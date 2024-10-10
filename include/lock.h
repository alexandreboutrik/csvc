#ifndef _CSVC_LOCK_H
#define _CSVC_LOCK_H

#include <stdint.h>

#define   LOCKFILE    "/tmp/csvc.lock"

void      LockEntry(const char *Region);
int8_t    CheckLock(const char *Region);
void      UnlockEntry(const char *Region);

#endif
