#!/bin/bash
LBLUE='\033[1;34m'
RED='\033[0;31m'
NC='\033[0m' # No Color
make
./simulator assembler/mandelbrot_text.bin ./assembler/mandelbrot_data.bin > man_result.bin
diff=$(cmp -l man_result.bin ans_man_result.bin | gawk '{printf "%08X %02X %02X\n", $1-1, strtonum(0$2), strtonum(0$3)}')
if [ -z "$diff" ]
then
  printf "${LBLUE}...passed test\n"
  printf "man_result.bin was successfully genereated!\n${NC}"
else
  printf "${RED}...failed test\n"
  printf "output man_result.bin would be wrong\n${NC}"
fi
