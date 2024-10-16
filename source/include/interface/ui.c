#include "interface/ui.h"

#include <err.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <termbox.h>

#include "data.h"

extern void
InitScreen(void)
{
  if (tb_init() != 0)
    err(errno, "tb_init");

  tb_enable_mouse();
  tb_hide_cursor();
}

extern void
Quit(cdata *Data)
{
  tb_shutdown();

  exit(EXIT_SUCCESS);
}

extern void
Error(cdata *Data, const int Errsv, const char* Func)
{
  tb_shutdown();

  if (Func != NULL)
    fprintf(stderr, "%s: ", Func);

  if (Errsv != 0)
    fprintf(stderr, "%s", strerror(Errsv));

  fprintf(stderr, "\n");
  exit(EXIT_FAILURE);
}

extern void
CheckWindowSize(cdata *Data)
{
  if (tb_width() < (ENTRY_MAX_SIZE*2))
    Error(Data, 0, "tb_width(): not enough columns");

  if (tb_height() < 16)
    Error(Data, 0, "tb_heigh(): not enough lines");
}

/* TODO: use tb_clear_screen() instead */
extern void
ClearScreen()
{
  tb_clear_buffer();

  int maxy = tb_height(), maxx = tb_width();

  for (int y = 0; y < maxy; y++)
    tb_empty(1, y, TB_BLACK, maxx);
}
