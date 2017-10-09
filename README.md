# simulator
使い方

アセンブリをアセンブルしてfibを動かす

まず、Node.jsをどうにか入れて下さい。

学科PC(ubuntu)の場合は

$ sudo apt-get update

$ sudo apt-get install nodejs

$ sudo ln -s /usr/bin/nodejs /usr/bin/node

でOKです。以下が本題です。

$ cd 好きなディレクトリ

$ git clone https://github.com/Tosh11/simulator.git

$ cd simulator

$ git checkout 1st

$ cd 1st/assembler

$ make && node main.js fib_edited.s > input.txt && ./main input.txt

これでアセンブルできました。

$ cd ..

$ make && ./simulator assembler/out.dat

これでGPR[1]に10946と出るはずです(フィボナッチ数列の第20項)


fib_edited.s を見ると、アセンブリが書いてあります。これをバイナリへアセンブルしたのです。
