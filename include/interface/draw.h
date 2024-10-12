#ifndef _CSVC_DRAW_H
#define _CSVC_DRAW_H

#include "data.h"

#define   SCREEN_MENU         0
#define   SCREEN_MODIFY       1
#define   SCREEN_ADD_ID       2
#define   SCREEN_ADD_REGION   3
#define   SCREEN_DELETE       4
#define   SCREEN_AOE          5
#define   SCREEN_DUPLICATED   6
#define   SCREEN_TOO_BIG      7

extern void     DrawScreen(const char *Filename, cdata *Data);

extern void     DrawMenu(const char *Filename, cdata *Data);
extern void     DrawModify(const char *Filename, cdata *Data);
extern void     DrawCreate_Id(const char *Filename, cdata *Data);
extern void     DrawCreate_Region(const char *Filename, cdata *Data);
extern void     DrawDelete(const char *Filename, cdata *Data);

/* ERROR screens */
extern void     DrawAOE(cdata *Data);
extern void     DrawDuplicated(cdata *Data);
extern void     DrawTooBig(cdata *Data);

#endif
