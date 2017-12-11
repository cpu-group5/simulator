#!/bin/bash
LBLUE='\033[1;34m'
RED='\033[0;31m'
NC='\033[0m' # No Color
make
node main.js minrt.s
./main minrt_text.dat minrt_text.bin
./main minrt_data.dat minrt_data.bin
text_diff=$(cmp -l minrt_text.bin ans_minrt_text.bin | gawk '{printf "%08X %02X %02X\n", $1-1, strtonum(0$2), strtonum(0$3)}')
data_diff=$(cmp -l minrt_data.bin ans_minrt_data.bin | gawk '{printf "%08X %02X %02X\n", $1-1, strtonum(0$2), strtonum(0$3)}')
if [ -z "$text_diff" ]
then
  printf "${LBLUE}...passed test\n"
  printf "minrt_text.bin was successfully genereated!\n${NC}"
else
  echo "$text_diff" > minrt_text.diff
  printf "${RED}...failed test\n"
  printf "output minrt_text.bin would be wrong\n${NC}"
fi
if [ -z "$data_diff" ]
then
  printf "${LBLUE}...passed test\n"
  printf "minrt_data.bin was successfully genereated!\n${NC}"
else
  printf "${RED}...failed test\n"
  printf "output minrt_data.bin would be wrong\n${NC}"
fi
