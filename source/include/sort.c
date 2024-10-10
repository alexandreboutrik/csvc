#include "sort.h"

#include <string.h>
#include <stdlib.h>

#include "data.h"

void
SwapEntry(cdata *Data, int i, int j)
{
  csvtable Tmp;

  strcpy(Tmp.Id, Data->Table[i].Id);
  strcpy(Tmp.Region, Data->Table[i].Region);

  strcpy(Data->Table[i].Id, Data->Table[j].Id);
  strcpy(Data->Table[i].Region, Data->Table[j].Region);

  strcpy(Data->Table[j].Id, Tmp.Id);
  strcpy(Data->Table[j].Region, Tmp.Region);
}

void 
InsertionSort(cdata *Data)
{
  int i, j;

  for (i = 0; i < Data->Table_Size; i++)
    for (j = i; (j > 0) && (atoi(Data->Table[j].Id) < atoi(Data->Table[j-1].Id)); j--)
      SwapEntry(Data, j, j-1);
}
