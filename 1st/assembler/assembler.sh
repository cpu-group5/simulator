#!/bin/bash
make
node main.js "$1.s"
./main "$1_text.dat" "$1_text.bin"
./main "$1_data.dat" "$1_data.dat"
