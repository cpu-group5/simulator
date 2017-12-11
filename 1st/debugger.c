#include "stdio.h"
#include "stdlib.h"
#include "simulator.h"

int WNSZ = 0x100;

void debug(simulator *self) {
  self->print_op(self);
  self->print_registers(self);
  while (1) {
    fprintf(stderr, "(type h to list commands)$");
    fgets(self->command, 256, stdin);
    switch (self->command[0]) {
      case '\n':
        break;
      case 'c':
        self->is_debug = 0;
        return;
      case 'j':
        switch (self->command[1]) {
          case ' ':
            self->stop_count = (unsigned long long) strtol(&self->command[2], NULL, 0);
            self->is_debug = 0;
            return;
          default:
            fprintf(stderr, "invalid\n");
        }
        break;
      case 'm':
        switch (self->command[1]) {
          case '\n':
            self->print_memory(self);
            break;
          case ' ':
            self->addr = (int) strtol(&self->command[2], NULL, 0);
            self->addr = (self->addr / WNSZ) * WNSZ;
            if (0 <= self->addr && self->addr < 0x80000) {
              print_memory(self);
            } else {
              fprintf(stderr, "invalid address\n");
            }
            break;
          case 'd':
            self->dhf = 0;
            break;
          case 'h':
            self->dhf = 1;
            break;
          case 'f':
            self->dhf = 2;
            break;
          default:
            fprintf(stderr, "invalid\n");
        }
        break;
      case 'u':
        if (self->addr - WNSZ >= 0) {
					self->addr -= WNSZ;
					print_memory(self);
				} else fprintf(stderr, "cannot go up any more\n");
        break;
      case 'd':
  			if (self->addr + WNSZ < 0x80000) {
					self->addr += WNSZ;
					print_memory(self);
				} else fprintf(stderr, "cannot go down any more\n");
        break;
      case 'b':
        switch (self->command[1]) {
          case '\n':
            self->print_breakpoints(self->breakpoints);
            break;
          case 'c':
            memset(self->breakpoints, 0, sizeof(int) * BREAKPOINTS_SIZE);
            break;
          case ' ':
            self->breakpoints[(int) strtol(&self->command[2], NULL, 0)] = 1;
            break;
          default:
            fprintf(stderr, "invalid\n");
        }
        break;
      case 'p':
        self->print_registers(self);
        break;
      case 'h':
        fprintf(stderr,
            "s [num] : 1 (指定されてればnum) ステップ実行\nc : 実質終了までずっと実行\nj num : 最初から数えてnum回命令が実行されるまで続ける\npj : (未実装)ジャンプ時にどこからどこへ行くかの表示のON/OFFの切り替え\np : レジスタの状態等を再表示する\nm [num]: メモリの内容を表示する。指定されてなければ前回と同じアドレスを参照する。\nu : 前回表示したメモリのアドレスより一ブロック分前のメモリの内容を表示する\nd : 前回表示したメモリのアドレスより一ブロック分後のメモリの内容を表示する\nmd : メモリの内容を次回から符号付き整数で表すようにする\nmh : メモリの内容を次回から16進数で表すようにする\nmf : メモリの内容を次回から小数表示で表すようにする\nb : ブレークポイントの表示\nb num : ブレークポイントにnumを追加\nbc : ブレークポイントの全削除\n");
        break;
      default:
        fprintf(stderr, "invalid\n");
    }
  }
  return;
}


void print_breakpoints(int breakpoints[]) {
  int i;
  for (i = 0; i < BREAKPOINTS_SIZE; i++) {
    if (breakpoints[i]) { fprintf(stderr, "%d\n", i); }
  }
  return;
};

void print_memory(simulator *self) {
  int line;
  if (self->dhf == 0) {
    for (line = self->addr; line < self->addr + WNSZ; line += 8) {
      fprintf(stderr, "%5X %8d %8d %8d %8d %8d %8d %8d %8d\n", line,
          self->DATA[line], self->DATA[line + 1], self->DATA[line + 2], self->DATA[line + 3],
          self->DATA[line + 4], self->DATA[line + 5], self->DATA[line + 6], self->DATA[line + 7]);
    }
  }
  if (self->dhf == 1) {
    for (line = self->addr; line < self->addr + WNSZ; line += 8) {
      fprintf(stderr, "%5X %8X %8X %8X %8X %8X %8X %8X %8X\n", line,
          self->DATA[line], self->DATA[line + 1], self->DATA[line + 2], self->DATA[line + 3],
          self->DATA[line + 4], self->DATA[line + 5], self->DATA[line + 6], self->DATA[line + 7]);
    }
  }
  if (self->dhf == 2) {
    for (line = self->addr; line < self->addr + WNSZ; line += 8) {
      fprintf(stderr, "%5X %8f %8f %8f %8f %8f %8f %8f %8f\n", line,
          *((float *) (self->DATA + line)), *((float *) (self->DATA + line + 1)),
          *((float *) (self->DATA + line + 2)), *((float *) (self->DATA + line + 3)),
          *((float *) (self->DATA + line + 4)), *((float *) (self->DATA + line + 5)),
          *((float *) (self->DATA + line + 6)), *((float *) (self->DATA + line + 7)));
    }
  }
}
