#!/bin/bash
make
node main.js fib.s
./main fib_text.dat fib_text.bin
./main fib_data.dat fib_data.bin
# diff fib_text.dat ans_fib_text.dat
