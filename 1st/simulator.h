#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__


#include <string.h>
#include <stdint.h>
#include "decoder.h"
#define R_MASK 0xFC00003F
#define IJ_MASK 0xFC000000
#define FL_MASK 0xFFE00000
#define GET_RS(x) ((0x03E00000 & (x)) >> 21)
#define GET_RT(x) ((0x001F0000 & (x)) >> 16)
#define GET_RD(x) ((0x0000F800 & (x)) >> 11)
#define GET_LC(x) (0x03FFFFFF & (x))
#define GET_SC(x) (0x0000FFFF & (x))
#define GET_SSC(x) ((0x000007C0 & (x)) >> 6)
#define GET_BCC(x) ((0x001C0000 & (x)) >> 18)
#define GET_FT(x) ((0x001F0000 & (x)) >> 16)
#define GET_FS(x) ((0x0000F800 & (x)) >> 11)
#define GET_FD(x) ((0x000007C0 & (x)) >> 6)
#define GET_CCC(x) ((0x00000700) & (x) >> 8)
#define GET_COND(x) (0x0000000F & (x))
#define GPR_SIZE 32
#define FPR_SIZE 32
#define BREAKPOINTS_SIZE 65536

typedef struct simulator{
  uint32_t GPR[GPR_SIZE]; // general purpose register
  float FPR[FPR_SIZE]; // floating point register
  uint32_t PC; // program counter
  uint32_t OP_CODE; // operation code
  uint32_t OP; // operation code
  char OP_DETAIL[128];
  uint32_t *TEXT;
  uint32_t *DATA;
  unsigned long long COUNT;
  int addr; // vars for memory print
  int dhf;
  FILE *IFILE;
  unsigned char FPCC; // floating point compare code
  int is_debug;
  int breakpoints[BREAKPOINTS_SIZE];
  unsigned long long stop_count;
  char command[256];
  decoder decoder;
  void (*init)(struct simulator *self, int argc, char const *argv[]);
  void (*fetch)(struct simulator *self);
  void (*exec)(struct simulator *self);
  void (*run)(struct simulator *self);
  void (*debug)(struct simulator *self);
  void (*print_op)(struct simulator *self);
  void (*print_registers)(struct simulator *self);
  void (*print_breakpoints)(int breakpoints[]);
  void (*print_memory)(struct simulator *self);
} simulator;
void init(simulator *self,int argc, char const *argv[]);
void fetch(simulator *self);
void run(simulator *self);
void print_registers(simulator *self);
void print_breakpoints(int breakpoints[]);
void print_memory(simulator *self);
void exec(simulator *self);
void debug(simulator *self);
void print_op(simulator *self);


#endif
