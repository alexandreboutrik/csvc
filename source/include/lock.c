#include "lock.h"

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "interface/ui.h"

void
LockEntry(const char *Id)
{
  FILE *File;

  if ((File = fopen(LOCKFILE, "a+")) == NULL)
    Error(NULL, errno, "LockEntry fopen");

  fprintf(File, " %s", Id);

  fclose(File);
}

int8_t
CheckLock(const char *Id)
{
  FILE  *File;
  char   input[256];
  int8_t ret;

  if ((File = fopen(LOCKFILE, "r")) == NULL)
    return 0;

  while (fgets(input, 256, File) != NULL)
  {
    if (! strcmp(input, Id))
    { fclose(File); return 1; }
  }

  fclose(File);
  return 0;
}

void
UnlockEntry(const char *Id, cdata *Data)
{
  FILE *File;
  char  input[256][256];
  int   i, j;

  if ((File = fopen(LOCKFILE, "r")) == NULL)
    return;
  for (i = 0; fscanf(File, "%s", &input[i][0]) != EOF; i++);
  fclose(File);

  if ((File = fopen(LOCKFILE, "w")) == NULL)
    Error(NULL, errno, "UnlockEntry fopen-w");
  for (j = 0; j < i; j++)
    if (strcmp(input[j], Id))
      fprintf(File, " %s", input[j]);
  fclose(File);
}
