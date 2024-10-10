#include "interface/input.h"

#include <ctype.h>
#include <termbox.h>
#include <string.h>
#include <stdint.h>

#include "interface/ui.h"
#include "csv.h"
#include "lock.h"

void
ZeroBuffer(cdata *Data)
{
  bzero(Data->buffer, strlen(Data->buffer));
  Data->bp = 0;
}

void
ChangeTo(cdata *Data, int8_t SCREEN)
{
  size_t size;

  if (SCREEN == SCREEN_MODIFY)
  {
    if (CheckLock(Data->Table[Data->sy].Region))
      SCREEN = SCREEN_AOE;
    else if (Data->sx == 0)
    {
      Data->bp = strlen(Data->Table[Data->sy].Id);
      strcpy(Data->buffer, Data->Table[Data->sy].Id);
      LockEntry(Data->buffer);
    }
    else
    {
      Data->bp = strlen(Data->Table[Data->sy].Region);
      strcpy(Data->buffer, Data->Table[Data->sy].Region);
      LockEntry(Data->buffer);
    }
  }

  if (SCREEN == SCREEN_ADD_ID)
    ZeroBuffer(Data);

  Data->Screen = SCREEN;
}

void
SaveToFile(const char *Filename, cdata *Data)
{
  UnlockEntry(Data->Table[Data->sy].Region);

  if (Data->sx == 0)
    strcpy(Data->Table[Data->sy].Id, Data->buffer);

  if (Data->sx == 1)
    strcpy(Data->Table[Data->sy].Region, Data->buffer);

  SaveCSV(Filename, Data);
  Data->Screen = SCREEN_MENU;
}

void
HandleInput(const char *Filename, cdata *Data)
{
  switch(Data->Event.type)
  {
    case TB_EVENT_KEY:
      HandleKey(Filename, Data);
      break;
    case TB_EVENT_RESIZE:
      tb_resize();
      CheckWindowSize(Data);
      break;
  }
}

void
HandleKey(const char *Filename, cdata *Data)
{
  int8_t aux = 0;

  switch (Data->Event.key)
  {
    case TB_KEY_ESC:
    case TB_KEY_CTRL_C:
      if (Data->Screen == SCREEN_MODIFY)
      { UnlockEntry(Data->Table[Data->sy].Region);}
      if (Data->Screen == SCREEN_MENU) { Quit(Data); }
      else { Data->Screen = SCREEN_MENU; }
      break;
    case TB_KEY_ARROW_UP:
      if (Data->Screen == SCREEN_MENU || Data->Screen == SCREEN_DELETE) 
      { Data->Event.ch = 'w'; }
      break;
    case TB_KEY_ARROW_LEFT:
      if (Data->Screen == SCREEN_MENU || Data->Screen == SCREEN_DELETE) 
      { Data->Event.ch = 'a'; }
      break;
    case TB_KEY_ARROW_DOWN:
      if (Data->Screen == SCREEN_MENU || Data->Screen == SCREEN_DELETE) 
      { Data->Event.ch = 's'; }
      break;
    case TB_KEY_ARROW_RIGHT:
      if (Data->Screen == SCREEN_MENU || Data->Screen == SCREEN_DELETE) 
      { Data->Event.ch = 'd'; }
      break;
    case TB_KEY_ENTER:
      if (Data->Screen == SCREEN_MENU) { ChangeTo(Data, SCREEN_MODIFY); aux = 1; }
      else if (Data->Screen == SCREEN_MODIFY) { SaveToFile(Filename, Data); }
      else if (Data->Screen == SCREEN_AOE) { Data->Screen = SCREEN_MENU; }
      else if (Data->Screen == SCREEN_ADD_ID || Data->Screen == SCREEN_ADD_REGION) 
      {
        AppendCSV(Filename, Data);
        ZeroBuffer(Data);
        if (Data->Screen == SCREEN_ADD_ID)
          Data->Screen = SCREEN_ADD_REGION; 
        else 
          Data->Screen = SCREEN_MENU;
        aux = 1;
      }
      else if (Data->Screen == SCREEN_DELETE) 
      {
        if (Data->s2 == 1) { DeleteCSV(Filename, Data); }
        Data->Screen = SCREEN_MENU;
      }
      break;
  }

  if (Data->Screen == SCREEN_MENU)
  {
    switch (Data->Event.ch)
    {
      case 'q': case 'Q':
        Quit(Data);
        break;
      case 'w': case 'W':
        if (Data->sy > 0)
          Data->sy--;
        break;
      case 'a': case 'A':
        if (Data->sx == 1)
          Data->sx = 0;
        break;
      case 's': case 'S':
        if (Data->sy < Data->Table_Size-1)
          Data->sy++;
        break;
      case 'd': case 'D':
        if (Data->sx == 0)
          Data->sx = 1;
        break;
      case 'e': case 'E':
        ChangeTo(Data, SCREEN_MODIFY); aux = 1;
        break;
      case 'c': case 'C':
        ChangeTo(Data, SCREEN_ADD_ID); aux = 1;
        break;
      case 'r': case 'R':
        ChangeTo(Data, SCREEN_DELETE);
        break;
    }
  }

  else if (Data->Screen == SCREEN_DELETE)
  {
    switch (Data->Event.ch)
    {
      case 'a': case 'A':
        if (Data->s2 == 1)
          Data->s2 = 0;
        break;
      case 'd': case 'D':
        if (Data->s2 == 0)
          Data->s2 = 1;
        break;
    }
  }

  if (aux == 1) { aux = 0; }
  else if (Data->Screen == SCREEN_MODIFY || Data->Screen == SCREEN_ADD_ID ||
    Data->Screen == SCREEN_ADD_REGION)
  {
    switch (Data->Event.key)
    {
      case TB_KEY_BACKSPACE:
        Data->bp--;
        Data->buffer[Data->bp] = '\0';
        break;
    }
    if ((Data->Event.ch >= 'a' && Data->Event.ch <= 'z') ||
      (Data->Event.ch >= 'A' && Data->Event.ch <= 'Z') ||
      (Data->Event.ch >= '0' && Data->Event.ch <= '9') ||
      Data->Event.ch == ' ')
    {
      if (Data->bp < 18)
      {
        Data->buffer[Data->bp++] = Data->Event.ch;
        Data->buffer[Data->bp] = '\0';
      }
    }
  }
}
