#ifndef _CSVC_UI_H
#define _CSVC_UI_H

#include "data.h"
#include "input.h"
#include "draw.h"

#define     COPYRIGHT       0x00A9

/* Characters */
#define     AC_ACUTE        0x00C1
#define     AC_TILDE        0x00C3
#define     C_CEDILLA       0x00C7
#define     EC_ACUTE        0x00C9
#define     OC_TILDE        0x00D5
#define     AS_GRAVE        0x00E0
#define     AS_ACUTE        0x00E1
#define     AS_CIRCF        0x00E2
#define     AS_TILDE        0x00E3
#define     S_CEDILLA       0x00E7
#define     ES_ACUTE        0x00E9
#define     ES_CIRCF        0x00EA
#define     IS_ACUTE        0x00ED
#define     OS_ACUTE        0x00F3
#define     OS_TILDE        0x00F5
#define     US_ACUTE        0x00FA

extern void     InitScreen(void);
extern void     Quit(cdata *Data);

extern void     Error(cdata *Data, const int Errsv, const char* Func);

extern void     CheckWindowSize(cdata *Data);
extern void     ClearScreen(void);

#endif
