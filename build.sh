#!/bin/bash

check_termbox=$(whereis termbox.h | wc -w)
if [ $check_termbox -lt 2 ]; then
  echo "Error: termbox.h required but not found."
  echo "Please install it: github.com/termbox/termbox2"
fi

mkdir -p ./bin

gcc -I./include -I./source source/main.c \
  source/include/interface/draw.c source/include/interface/input.c \
  source/include/interface/ui.c \
  source/include/data.c source/include/csv.c source/include/lock.c \
  source/include/sort.c \
  -o ./bin/csvc-$(uname -m)-$(uname -s) -static -Wl,-Bstatic -ltermbox $*

if [ $? -eq 0 ] ; then
  echo "Compiled successfully."
else
  echo "Compiling FAILED."
fi
