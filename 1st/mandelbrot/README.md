assembler/mandelbrot.sが、対象とするアセンブリです。

$ cd ./assembler

$ make

$ ./ass mandelbrot.s result

$ cd ../sim2

$ make

$ ./sim ../assembler/text ../assembler/data ifile > ouput

で、結果がouputにバイナリで入っています。

手順は適当に書いたので間違い等あるかもしれませんが...
