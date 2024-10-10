#ifndef _CSVC_CSV_H
#define _CSVC_CSV_H

#include "data.h"

void      ReadCSV(const char *Filename, cdata *Data);
void      SaveCSV(const char *Filename, cdata *Data);
void      DeleteCSV(const char *Filename, cdata *Data);
void      AppendCSV(const char *Filename, cdata *Data);

#endif
