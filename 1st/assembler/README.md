アセンブルしたいファイルを、このディレクトリへ移動します。

まず、Node.jsをどうにか入れて下さい。(ubuntuの場合の参考:https://qiita.com/seibe/items/36cef7df85fe2cefa3ea)

たとえば、fib.sをアセンブルする場合は

./assembler.sh fib

として下さい。

他にも中間体のファイルは生成されますが、下の3ファイルが使い道のあるものです。

fib_text.bin, fib_data.bin, pclist_fib.log

各ファイルの説明です。

fib_text.bin

本体です。シミュレータに渡されます。

fib_data.bin

浮動小数定数などは、始めにメモリに保存する必要があります。その浮動小数定数などを羅列しています。シミュレータに渡されます。ちなみに、fibの場合は空ファイルになります。

pclist_fib.log

は、PCとラベル、命令の対応を確認したい時に参照して下さい。

次に、1st/README.mdを読んでシミュレーションして下さい。
