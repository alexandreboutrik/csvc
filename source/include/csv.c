#include "csv.h"

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>

#include "interface/ui.h"
#include "sort.h"

static inline void
SkipLine(FILE *File)
{
  fscanf(File, "%*[^\n]%*c");
}

void
ReadCSV(const char *Filename, cdata *Data)
{
  FILE *File;
  char  input[256];

  int64_t i;
  char    ch;

  bzero(&input, 256);
  Data->Table_Size = 0;

  if ((File = fopen(Filename, "r")) == NULL)
    Error(Data, errno, "ReadCSV fopen");

  SkipLine(File);

  Data->Table_Size = 0;
  while (fscanf(File, "%[^,]%*c \"%[^\n]%*c", Data->Table[Data->Table_Size].Id, Data->Table[Data->Table_Size].Region) != EOF)
  {
    Data->Table[Data->Table_Size].Region[strlen(Data->Table[Data->Table_Size].Region)-1] = '\0';
    Data->Table_Size++;
  }

  InsertionSort(Data);

  fclose(File);
}

void
SaveCSV(const char *Filename, cdata *Data)
{
  FILE *File;
  int   i;

  if ((File = fopen(Filename, "w")) == NULL)
    Error(Data, errno, "ReadCSV fopen");

  fprintf(File, "\"Id\",\"Name\"\n");
  for (i = 0; i < Data->Table_Size; i++)
    fprintf(File, "%s,\"%s\"\n", Data->Table[i].Id, Data->Table[i].Region);

  fclose(File);
}

void
DeleteCSV(const char *Filename, cdata *Data)
{
  int i;

  for (i = Data->sy; i < Data->Table_Size; i++)
  {
    strcpy(Data->Table[i].Id, Data->Table[i+1].Id);
    strcpy(Data->Table[i].Region, Data->Table[i+1].Region);
  }

  Data->Table_Size--;

  SaveCSV(Filename, Data);
}

int8_t
CheckDuplicated(cdata *Data)
{
  int i;

  for (i = 0; i < Data->Table_Size; i++)
    if (! strcmp(Data->Table[i].Id, Data->buffer))
      return 1;

  return 0;
}

void
AppendCSV(const char *Filename, cdata *Data)
{
  if (! CheckDuplicated(Data))
  {
    if (Data->Screen == SCREEN_ADD_ID)
      strcpy(Data->Table[Data->Table_Size].Id, Data->buffer);
    else
    {
      strcpy(Data->Table[Data->Table_Size].Region, Data->buffer);
      Data->Table_Size++;
    }

    SaveCSV(Filename, Data);
  }
  else {
    Data->Screen = SCREEN_DUPLICATED;
  }
}
