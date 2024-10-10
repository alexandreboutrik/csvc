#include "lock.h"

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "interface/ui.h"

void
LockEntry(const char *Region)
{
  FILE *File;

  if ((File = fopen(LOCKFILE, "a+")) == NULL)
    Error(NULL, errno, "LockEntry fopen");

  fprintf(File, "\n%s", Region);

  fclose(File);
}

int8_t
CheckLock(const char *Region)
{
  FILE  *File;
  char   input[256];
  int8_t ret;

  if ((File = fopen(LOCKFILE, "r")) == NULL)
    return 0;

  while (fgets(input, 256, File) != NULL)
  {
    if (! strcmp(input, Region))
    { fclose(File); return 1; }
  }

  fclose(File);
  return 0;
}

void
UnlockEntry(const char *Region)
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
    if (strcmp(input[j], Region))
      fprintf(File, " %s", input[j]);
  fclose(File);
}
