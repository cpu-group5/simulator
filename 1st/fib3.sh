#!/bin/bash
make clean
make
./simulator ./assembler/fib3_text.bin ./assembler/fib3_data.bin ./ifile.bin > fib3.bin
