#!/bin/bash
LBLUE='\033[1;34m'
RED='\033[0;31m'
NC='\033[0m' # No Color
make
node main.js mandelbrot.s
./main mandelbrot_text.dat mandelbrot_text.bin
./main mandelbrot_data.dat mandelbrot_data.bin
text_diff=$(cmp -l mandelbrot_text.bin ans_mandelbrot_text.bin | gawk '{printf "%08X %02X %02X\n", $1-1, strtonum(0$2), strtonum(0$3)}')
data_diff=$(cmp -l mandelbrot_data.bin ans_mandelbrot_data.bin | gawk '{printf "%08X %02X %02X\n", $1-1, strtonum(0$2), strtonum(0$3)}')
if [ -z "$text_diff" ]
then
  printf "${LBLUE}...passed test\n"
  printf "mandelbrot_text.bin was successfully genereated!\n${NC}"
else
  printf "${RED}...failed test\n"
  printf "output mandelbrot_text.bin would be wrong\n${NC}"
fi
if [ -z "$data_diff" ]
then
  printf "${LBLUE}...passed test\n"
  printf "mandelbrot_data.bin was successfully genereated!\n${NC}"
else
  printf "${RED}...failed test\n"
  printf "output mandelbrot_data.bin would be wrong\n${NC}"
fi
