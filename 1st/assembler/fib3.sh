#!/bin/bash
make
node main.js fib3.s
./main fib3_text.dat fib3_text.bin
./main fib3_data.dat fib3_data.bin
# diff fib_text.dat ans_fib_text.dat
