#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <locale.h>
#include <termbox.h>

#include "csv.h"
#include "interface/ui.h"
#include "data.h"

int
main(int argc, const char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "usage: ./csvc.exe <filename>\n");
    return EINVAL;
  }

  setlocale(LC_ALL, "Portuguese");

  cdata Data;

  InitScreen();

  InitData(&Data);

  while (tb_peek_event(&(Data.Event), 30) != -1)
  {
    ReadCSV(argv[1], &Data);

    ClearScreen();

    HandleInput(argv[1], &Data);

    DrawScreen(argv[1], &Data);

    tb_render();
  }

  Quit(&Data);

  return 0;
}
