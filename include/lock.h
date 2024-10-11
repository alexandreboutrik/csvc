#ifndef _CSVC_LOCK_H
#define _CSVC_LOCK_H

#include <stdint.h>

#include "data.h"

#define   LOCKFILE    "/tmp/csvc.lock"

/*
 * we use a LOCKFILE to check if the entry is already opened for editing
 * by another csvc process.
 */

extern void     LockEntry(const char *Id);
extern int8_t   CheckLock(const char *Id);
extern void     UnlockEntry(const char *Id, cdata *Data);

#endif
