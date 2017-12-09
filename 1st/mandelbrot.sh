#!/bin/bash
make
./simulator assembler/mandelbrot_text.bin ./assembler/mandelbrot_data.bin > man_result.bin
# cmp -l man_result.bin ans_man_result.bin | gawk '{printf "%08X %02X %02X\n", $1-1, strtonum(0$2), strtonum(0$3)}'
