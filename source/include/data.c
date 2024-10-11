#include "data.h"

#include <stdlib.h>

extern void
InitData(cdata *Data)
{
  Data->Table_Size = 0;

  Data->sx = 0; Data->sy = 0;
  Data->s2 = 0;

  Data->buffer[0] = '\0';
  Data->bp = 0;
}
