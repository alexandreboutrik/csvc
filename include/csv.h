#ifndef _CSVC_CSV_H
#define _CSVC_CSV_H

#include <stdint.h>

#include "data.h"

extern void     ReadCSV(const char *Filename, cdata *Data);
extern void     SaveCSV(const char *Filename, cdata *Data);
extern void     DeleteCSV(const char *Filename, cdata *Data);
extern void     AppendCSV(const char *Filename, cdata *Data);

extern int8_t   CheckDuplicated(cdata *Data);

#endif
