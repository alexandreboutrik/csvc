#include "interface/draw.h"

#include <string.h>
#include <termbox.h>

#include "data.h"
#include "interface/ui.h"

#define SELECTED_BG TB_WHITE
#define SELECTED_FG TB_GREY

static inline void
PrintLine(int maxx, int line)
{
  int i;
  for (i = 0; i < maxx; i++)
  {
    tb_char(i, line, TB_WHITE, TB_BLACK, '-');
    tb_char(i, line, TB_WHITE, TB_BLACK, '-');
  }
}

extern void
DrawScreen(const char *Filename, cdata *Data)
{
  CheckWindowSize(Data);

  switch (Data->Screen)
  {
    case SCREEN_MENU:
      DrawMenu(Filename, Data);
      break;
    case SCREEN_MODIFY:
      DrawModify(Filename, Data);
      break;
    case SCREEN_ADD_ID:
      DrawCreate_Id(Filename, Data);
      break;
    case SCREEN_ADD_REGION:
      DrawCreate_Region(Filename, Data);
      break;
    case SCREEN_DELETE:
      DrawDelete(Filename, Data);
      break;
    case SCREEN_AOE:
      DrawAOE(Data);
      break;
    case SCREEN_DUPLICATED:
      DrawDuplicated(Data);
      break;
  }
}

extern void
DrawModify(const char *Filename, cdata *Data)
{
  tb_string(2, 1, TB_WHITE, TB_BLACK, "EDIT");
  tb_string(2, 3, TB_WHITE, TB_BLACK, "Digite um novo valor: '");
  tb_string(25, 3, SELECTED_FG, SELECTED_BG, Data->buffer);
  tb_char(25+Data->bp, 3, TB_WHITE, TB_BLACK, '\'');
}

extern void
DrawCreate_Id(const char *Filename, cdata *Data)
{
  tb_string(2, 1, TB_WHITE, TB_BLACK, "CREATE");
  tb_string(2, 3, TB_WHITE, TB_BLACK, "Digite um novo Id: '");
  tb_string(22, 3, SELECTED_FG, SELECTED_BG, Data->buffer);
  tb_char(22+Data->bp, 3, TB_WHITE, TB_BLACK, '\'');
}

extern void
DrawCreate_Region(const char *Filename, cdata *Data)
{
  tb_string(2, 1, TB_WHITE, TB_BLACK, "CREATE");
  tb_string(2, 3, TB_WHITE, TB_BLACK, "Id salvo.");
  tb_string(2, 4, TB_WHITE, TB_BLACK, "Digite uma nova regi");
  tb_char(22, 4, TB_WHITE, TB_BLACK, AS_TILDE);
  tb_string(23, 4, TB_WHITE, TB_BLACK, "o: '");
  tb_string(27, 4, SELECTED_FG, SELECTED_BG, Data->buffer);
  tb_char(27+Data->bp, 4, TB_WHITE, TB_BLACK, '\'');
}

extern void
DrawDelete(const char *Filename, cdata *Data)
{
  int i;

  tb_string(2, 1, TB_WHITE, TB_BLACK, "REMOVE");
  tb_string(2, 3, TB_WHITE, TB_BLACK, "Deseja realmente remover  ");
  tb_string(28, 3, TB_WHITE, TB_BLACK, Data->Table[Data->sy].Region);

  if (Data->s2 == 0)
  {
    tb_char(2, 5, SELECTED_FG, SELECTED_BG, 'N');
    tb_char(3, 5, SELECTED_FG, SELECTED_BG, AS_TILDE);
    tb_char(4, 5, SELECTED_FG, SELECTED_BG, 'o');
    tb_string(5, 5, SELECTED_FG, SELECTED_BG, "   *");
  } else {
    tb_char(2, 5, TB_WHITE, TB_BLACK, 'N');
    tb_char(3, 5, TB_WHITE, TB_BLACK, AS_TILDE);
    tb_char(4, 5, TB_WHITE, TB_BLACK, 'o');
  }

  if (Data->s2 == 1)
    tb_string(12, 5, SELECTED_FG, SELECTED_BG, "Sim   *");
  else
    tb_string(12, 5, TB_WHITE, TB_BLACK, "Sim");
}

extern void
DrawAOE(cdata *Data)
{
  tb_string(2, 1, TB_WHITE, TB_BLACK, "! ERROR !");

  tb_string(2, 3, TB_WHITE, TB_BLACK, "Essa entrada j");
  tb_char(16, 3, TB_WHITE, TB_BLACK, AS_ACUTE);
  tb_string(17, 3, TB_WHITE, TB_BLACK, " foi aberta por outra");
  tb_string(2, 4, TB_WHITE, TB_BLACK, "inst");
  tb_char(6, 4, TB_WHITE, TB_BLACK, AS_CIRCF);
  tb_string(7, 4, TB_WHITE, TB_BLACK, "ncia CSVC.");

  tb_string(2, 5, TB_WHITE, TB_BLACK, "Clique ENTER para voltar");
  tb_string(2, 7, SELECTED_FG, SELECTED_BG, "Ok   *");
}

extern void
DrawDuplicated(cdata *Data)
{
  tb_string(2, 1, TB_WHITE, TB_BLACK, "! ERROR !");

  tb_string(2, 3, TB_WHITE, TB_BLACK, "Essa entrada j");
  tb_char(16, 3, TB_WHITE, TB_BLACK, AS_ACUTE);
  tb_string(17, 3, TB_WHITE, TB_BLACK, " foi inserida.");

  tb_string(2, 4, TB_WHITE, TB_BLACK, "Clique ENTER para voltar");
  tb_string(2, 6, SELECTED_FG, SELECTED_BG, "Ok   *");
}

extern void
DrawMenu(const char *Filename, cdata *Data)
{
  size_t size;
  int maxx = tb_width();
  int i, j;

  tb_string(2, 1, TB_WHITE, TB_BLACK, "file: ");
  tb_string(8, 1, TB_WHITE, TB_BLACK, Filename);

  PrintLine(maxx, 2);
  PrintLine(maxx, 4);

  tb_string(2, 3, TB_WHITE, TB_BLACK, "Id");
  tb_char(10, 3, TB_WHITE, TB_BLACK, '|');
  tb_string(12, 3, TB_WHITE, TB_BLACK, "Name");

  tb_string(3, 5+Data->Table_Size+1, TB_WHITE, TB_BLACK, "(c)reate");
  tb_string(3, 5+Data->Table_Size+2, TB_WHITE, TB_BLACK, "(e)edit");
  tb_string(3, 5+Data->Table_Size+3, TB_WHITE, TB_BLACK, "(r)emove");

  tb_char(2, 5+Data->Table_Size+5, TB_WHITE, TB_BLACK, COPYRIGHT);
  tb_string(4, 5+Data->Table_Size+5, TB_WHITE, TB_BLACK, "2024 Boutrik");

  for (i = 0; i < Data->Table_Size; i++)
  {
    if (i == Data->sy && Data->sx == 0)
    {
      size = strlen(Data->Table[i].Id);
      tb_string(2, 5+i, SELECTED_FG, SELECTED_BG, Data->Table[i].Id);
      for (j = 0; j < 7-size; j++)
        tb_char(2+size+j, 5+i, SELECTED_BG, SELECTED_BG, ' ');
      tb_char(2+size+j-1, 5+i, SELECTED_FG, SELECTED_BG, '*');
    }
    else
      tb_string(2, 5+i, TB_WHITE, TB_BLACK, Data->Table[i].Id);

    tb_char(10, 5+i, TB_WHITE, TB_BLACK, '|');

    if (i == Data->sy && Data->sx == 1)
    {
      size = strlen(Data->Table[i].Region);
      tb_string(12, 5+i, SELECTED_FG, SELECTED_BG, Data->Table[i].Region);
      for (j = 0; j < 20-size; j++)
        tb_char(12+size+j, 5+i, SELECTED_BG, SELECTED_BG, ' ');
      tb_char(12+size+j-1, 5+i, SELECTED_FG, SELECTED_BG, '*');
    }
    else
      tb_string(12, 5+i, TB_WHITE, TB_BLACK, Data->Table[i].Region);
  }
}
