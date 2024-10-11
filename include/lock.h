#ifndef _CSVC_LOCK_H
#define _CSVC_LOCK_H

#include <stdint.h>

#include "data.h"

#define   LOCKFILE    "/tmp/csvc.lock"

void      LockEntry(const char *Id);
int8_t    CheckLock(const char *Id);
void      UnlockEntry(const char *Id, cdata *Data);

#endif
