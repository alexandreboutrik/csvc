#ifndef _CSVC_DATA_H
#define _CSVC_DATA_H

#include <stdio.h>
#include <stdint.h>
#include <termbox.h>

typedef struct csvtable csvtable;
struct csvtable
{
  char       Id[8];         /* region id */
  char       Region[256];     /* region name */

  int8_t     Active;        /* 'being edited' flag */
};

typedef struct cdata cdata;
struct cdata
{
  int8_t     Screen;        /* current screen to draw */

  csvtable   Table[256];    /* array of csvtable */
  uint16_t   Table_Size;    /* table size */

  int8_t     sx, sy;        /* 'selected' coordenates */
  int8_t     s2;            /* 'selected' for DELETE screen */

  char       buffer[256];   /* buffer for the MODIFY screen */
  uint8_t    bp;            /* buffer pointer, size */

  struct tb_event Event;    /* termbox event */
};

extern void     InitData(cdata *Data);

#endif
