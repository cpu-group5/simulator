#include "stdio.h"
#include "stdlib.h"
#include "simulator.h"

void debug(simulator *self){
  while (self->is_debug||self->breakpoints[self->PC-1]) {
    fprintf(stderr,"(type h to list commands)$");
    fgets(self->command, 256, stdin);
    switch (self->command[0]) {
      case '\n':
        return;
      case 'b':
        switch (self->command[1]) {
        case '\n':
          self->print_breakpoints(self->breakpoints);
          break;
        case ' ':
          self->breakpoints[(int)strtol(&self->command[2], NULL, 0)] = 1;
          break;
        default:
          fprintf(stderr,"invalid\n");
        }
        break;
      case 'c':
        self->is_debug = 0;
        return;
      case 'h':
        fprintf(stderr,"c : 実質終了までずっと実行\ns [num] : 1 (指定されてればnum) ステップ実行\nc : 実質終了までずっと実行\nj num : 最初から数えてnum回命令が実行されるまで続ける\npj : ジャンプ時にどこからどこへ行くかの表示のON/OFFの切り替え\np : レジスタの状態等を再表示する\nm [num]: メモリの内容を表示する。指定されてなければ前回と同じアドレスを参照する。\nu : 前回表示したメモリのアドレスより一ブロック分前のメモリの内容を表示する\nd : 前回表示したメモリのアドレスより一ブロック分後のメモリの内容を表示する\nmd : メモリの内容を次回から符号付き整数で表すようにする\nmh : メモリの内容を次回から16進数で表すようにする\nmf : メモリの内容を次回から小数表示で表すようにする\nb : ブレークポイントの表示\nb num : ブレークポイントにnumを追加\nbc : ブレークポイントの全削除\nps : 現在の統計情報を表示する");
        break;
      default:
        fprintf(stderr,"invalid\n");
    }
  }
  return;
}
