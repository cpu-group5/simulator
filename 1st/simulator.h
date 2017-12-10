#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#include <stdint.h>
#include "decoder.h"
#define GPR_SIZE 32
#define FPR_SIZE 32

typedef struct simulator{
  uint32_t GPR[GPR_SIZE]; // general purpose register
  float FPR[FPR_SIZE]; // floating point register
  uint32_t PC; // program counter
  uint32_t OP_CODE; // operation code
  uint32_t OP; // operation code
  uint32_t *TEXT;
  uint32_t *DATA;
  unsigned long long COUNT;
  FILE *IFILE;
  unsigned char FPCC; // floating point compare code
  decoder decoder;
  void (*init)(struct simulator *self, int argc, char const *argv[]);
  void (*fetch)(struct simulator *self);
  void (*exec)(struct simulator *self);
  void (*run)(struct simulator *self);
  void (*print_registers)(struct simulator *self);
} simulator;
void init(simulator *self,int argc, char const *argv[]);
void fetch(simulator *self);
void run(simulator *self);
void print_registers(simulator *self);

#endif
