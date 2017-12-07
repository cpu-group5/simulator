#!/bin/bash
make && node main.js fib_edited.s && ./main fib_edited_text.dat
diff fib_edited_text.dat ans_fib_edited_text.dat
