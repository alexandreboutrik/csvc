#ifndef _CSVC_DRAW_H
#define _CSVC_DRAW_H

#include "data.h"

#define   SCREEN_MENU         0
#define   SCREEN_MODIFY       1
#define   SCREEN_ADD_ID       2
#define   SCREEN_ADD_REGION   3
#define   SCREEN_DELETE       4
#define   SCREEN_AOE          5

/* Functions */
void      DrawScreen(const char *Filename, cdata *Data);

void      DrawMenu(const char *Filename, cdata *Data);
void      DrawModify(const char *Filename, cdata *Data);
void      DrawCreate_Id(const char *Filename, cdata *Data);
void      DrawCreate_Region(const char *Filename, cdata *Data);
void      DrawDelete(const char *Filename, cdata *Data);
void      DrawAOE(const char *Filename, cdata *Data);

#endif
