#!/bin/bash
make
node main.js mandelbrot.s
./main mandelbrot_text.dat mandelbrot_text.bin
./main mandelbrot_data.dat mandelbrot_data.bin
cmp -l mandelbrot_text.bin ans_mandelbrot_text.bin | gawk '{printf "%08X %02X %02X\n", $1-1, strtonum(0$2), strtonum(0$3)}'
cmp -l mandelbrot_data.bin ans_mandelbrot_data.bin | gawk '{printf "%08X %02X %02X\n", $1-1, strtonum(0$2), strtonum(0$3)}'
