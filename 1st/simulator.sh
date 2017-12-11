#!/bin/bash
LBLUE='\033[1;34m'
RED='\033[0;31m'
NC='\033[0m' # No Color
make clean
make
./simulator "assembler/$1_text.bin" "assembler/$1_data.bin" "$2" > "$1_result.bin"
