#include "csv.h"

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>

#include "data.h"
#include "interface/draw.h"
#include "interface/ui.h"
#include "sort.h"

static inline void
SkipLine(FILE *File)
{
  // read until newline
  fscanf(File, "%*[^\n]%*c");
}

extern void
ReadCSV(const char *Filename, cdata *Data)
{
  FILE *File;
  char  input[CSV_MAX_SIZE];

  int64_t i;
  char    ch;

  bzero(&input, CSV_MAX_SIZE);
  Data->Table_Size = 0;

  if ((File = fopen(Filename, "r")) == NULL)
    Error(Data, errno, "ReadCSV fopen");

  SkipLine(File);

  // load the file data to Data->Table
  Data->Table_Size = 0;
  while (fscanf(File, "%[^,]%*c \"%[^\n]%*c", Data->Table[Data->Table_Size].Id, Data->Table[Data->Table_Size].Region) != EOF)
  {
    if (Data->Table_Size >= CSV_MAX_SIZE)
      Error(Data, 1, "ReadCSV: too many entries, CSV is too big");

    Data->Table[Data->Table_Size].Region[strlen(Data->Table[Data->Table_Size].Region)-1] = '\0';
    Data->Table_Size++;
  }

  // sort the entries by ID
  InsertionSort(Data);

  fclose(File);
}

/*
 * Save Data->Table to the CSV file
 */ 
extern void
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

/*
 * Delete an entry from the CSV file
 * first delete it from Data->Table
 * then use SaveCSV to save Data->Table to file
 */ 
extern void
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

/*
 * Check if there is already an entry with the ID
 */ 
extern int8_t
CheckDuplicated(cdata *Data)
{
  int i;

  for (i = 0; i < Data->Table_Size; i++)
    if (! strcmp(Data->Table[i].Id, Data->buffer))
      return 1;

  return 0;
}

extern int8_t
IntegerConstraint(const char *string, size_t size)
{
  size_t i;

  for (i = 0; i < size; i++)
    if (string[i] < '0' || string[i] > '9')
      return 0;

  return 1;
}

extern void
AppendCSV(const char *Filename, cdata *Data)
{
  /* check if its not an duplicated entry */
  if (! CheckDuplicated(Data))
  {
    if (Data->Screen == SCREEN_ADD_ID)
    {
      if (IntegerConstraint(Data->buffer, Data->bp))
        strcpy(Data->Table[Data->Table_Size].Id, Data->buffer);
      else
        Data->Screen = SCREEN_INT_CT;
    } else {
      strcpy(Data->Table[Data->Table_Size].Region, Data->buffer);
      Data->Table_Size++;
    }

    SaveCSV(Filename, Data);
  }
  else {
    Data->Screen = SCREEN_DUPLICATED;
  }
}
