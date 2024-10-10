#include "data.h"

#include <stdlib.h>

void
InitData(cdata *Data)
{
  int i;

  for (i = 0; i < 65536; i++)
    Data->cindex[i] = FALSE;

  Data->Table_Size = 0;

  Data->sx = 0; Data->sy = 0;
  Data->s2 = 0;

  Data->buffer[0] = '\0';
  Data->bp = 0;
}
