#!/bin/bash
make
node main.js fib_edited.s
./main fib_edited_text.dat fib_edited_text.bin
./main fib_edited_data.dat fib_edited_data.bin
diff fib_edited_text.dat ans_fib_edited_text.dat
