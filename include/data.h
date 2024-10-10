#ifndef _CSVC_DATA_H
#define _CSVC_DATA_H

#include <stdio.h>
#include <stdint.h>
#include <termbox.h>

#define FALSE 0
#define TRUE  1

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

  int8_t     cindex[65536]; /* index showing which IDs were inserted */
  csvtable   Table[256];    /* array of csvtable */
  uint16_t   Table_Size;    /* table size */

  int8_t     sx, sy;        /* 'selected' coordenates */
  int8_t     s2;            /* 'selected' for DELETE screen */

  char       buffer[256];   /* buffer for the MODIFY screen */
  uint8_t    bp;            /* buffer pointer, size */

  struct tb_event Event;    /* termbox event */
};

/* Functions */
void      InitData(cdata *Data);

#endif
