#!/bin/bash
LBLUE='\033[1;34m'
RED='\033[0;31m'
NC='\033[0m' # No Color
make
# sudo gdb --args ./simulator assembler/minrt_text.bin ./assembler/minrt_data.bin ./minrt_ifile.bin
./simulator assembler/minrt_text.bin ./assembler/minrt_data.bin ./minrt_ifile.bin > minrt_result.ppm
diff=$(cmp -l minrt_result.ppm ans_minrt_result.ppm | gawk '{printf "%08X %02X %02X\n", $1-1, strtonum(0$2), strtonum(0$3)}')
if [ -z "$diff" ]
then
  printf "${LBLUE}...passed test\n"
  printf "minrt_result.ppm was successfully genereated!\n${NC}"
else
  printf "${RED}...failed test\n"
  printf "output minrt_result.ppm would be wrong\n${NC}"
fi
