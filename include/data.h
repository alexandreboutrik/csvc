#ifndef _CSVC_DATA_H
#define _CSVC_DATA_H

#include <stdio.h>
#include <stdint.h>
#include <termbox.h>

#define   CSV_MAX_SIZE    256
#define   ENTRY_MAX_SIZE  18

typedef struct csvtable csvtable;
struct csvtable
{
  char       Id[8];                 /* region id */
  char       Region[CSV_MAX_SIZE];  /* region name */
};

typedef struct cdata cdata;
struct cdata
{
  int8_t     Screen;                /* current screen to draw */

  csvtable   Table[CSV_MAX_SIZE];   /* array of csvtable */
  uint16_t   Table_Size;            /* table size */

  int8_t     sx, sy;                /* 'selected' coordenates */
  int8_t     s2;                    /* 'selected' for DELETE screen */

  char       buffer[CSV_MAX_SIZE];  /* buffer for the EDIT screens */
  uint8_t    bp;                    /* buffer pointer, buffer size */

  struct tb_event Event;            /* termbox event */
};

extern void     InitData(cdata *Data);

#endif
