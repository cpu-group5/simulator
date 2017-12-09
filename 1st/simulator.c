#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "simulator.h"

uint32_t *open_TEXT(simulator *self, int argc, char const *argv[]){
  FILE *file_pointer = fopen(argv[1], "r");
  char debug = argv[2];
  char byte[4];
  uint32_t *TEXT = malloc(1024*1024*2);
  int counter = 0;
    uint32_t tmp;
  if (file_pointer == NULL) {
    fprintf(stderr, "Can't open input file\n");
    perror("open_TEXT");
    exit(1);
  }
  while (fscanf(file_pointer, "%c%c%c%c", &byte[0], &byte[1], &byte[2], &byte[3]) != EOF) {
    tmp = *(uint32_t *) byte;
    TEXT[counter++] = tmp;
  }
  return TEXT;
}

uint32_t *open_DATA(simulator *self, int argc, char const *argv[]){
  FILE *file_pointer = fopen(argv[2], "r");
  char debug = argv[2];
  char byte[4];
  uint32_t *DATA = malloc(1024*1024*2);
  int counter = 0;
    uint32_t tmp;
  if (file_pointer == NULL) {
    fprintf(stderr, "Can't open input file\n");
    perror("open_DATA");
    exit(1);
  }
  while (fscanf(file_pointer, "%c%c%c%c", &byte[0], &byte[1], &byte[2], &byte[3]) != EOF) {
    tmp = *(uint32_t *) byte;
    printf("%f\n", tmp);
    DATA[counter++] = tmp;
  }
  fprintf(stderr, "%s\n", argv[2]);
  fprintf(stderr, "%f\n", DATA[0]);
  fprintf(stderr, "%f\n", DATA[1]);
  fprintf(stderr, "%f\n", DATA[2]);
  fprintf(stderr, "%f\n", DATA[3]);
  return DATA;
}

void init(simulator *self,int argc, char const *argv[]){
  decoder decoder;
  init_decoder(&decoder);
  memset(self->GPR, 0, sizeof(int) * GPR_SIZE);
  memset(self->FPR, 0.0, sizeof(float) * FPR_SIZE);
  self->GPR[0] = 0;
	// self->GPR[29] = fsize/4;
	self->GPR[30] = 40000;
  self->PC = 0;
  self->decoder = decoder;
  self->fetch = fetch;
  self->run = run;
  self->print_registers = print_registers;
  self->TEXT = open_TEXT(self, argc, argv);
  self->DATA = open_DATA(self, argc, argv);
  self->COUNT = 0;
};

void run(simulator *self){
  for (; ;) {
    self->fetch(self);
    self->OP = self->decoder.decode(&(self->decoder), self->OP_CODE);
    // self->print_registers(self);
    if (self->OP == undefined) {
      self->print_registers(self);
      exit(1);
    }
    self->exec(self);
  }
  self->print_registers(self);
};

void print_registers(simulator *self) {
  fprintf(stderr,"%d\tPC: %d\tOP_CODE:%08X\tFPCC: %02X\nGPR\n0-3\t%d\t%d\t%d\t%d\n4-7\t%d\t%d\t%d\t%d\n8-11\t%d\t%d\t%d\t%d\n12-15\t%d\t%d\t%d\t%d\n16-19\t%d\t%d\t%d\t%d\n20-23\t%d\t%d\t%d\t%d\n24-27\t%d\t%d\t%d\t%d\n28-31\t%d\t%d\t%d\t%d\nFPR\n0-3\t%f\t%f\t%f\t%f\n4-7\t%f\t%f\t%f\t%f\n8-11\t%f\t%f\t%f\t%f\n12-15\t%f\t%f\t%f\t%f\n16-19\t%f\t%f\t%f\t%f\n20-23\t%f\t%f\t%f\t%f\n24-27\t%f\t%f\t%f\t%f\n28-31\t%f\t%f\t%f\t%f\n\n\n", self->COUNT-1, self->PC-1, self->OP_CODE, self->FPCC, self->GPR[0], self->GPR[1], self->GPR[2], self->GPR[3], self->GPR[4], self->GPR[5], self->GPR[6], self->GPR[7], self->GPR[8], self->GPR[9], self->GPR[10], self->GPR[11], self->GPR[12], self->GPR[13], self->GPR[14], self->GPR[15], self->GPR[16], self->GPR[17], self->GPR[18], self->GPR[19], self->GPR[20], self->GPR[21], self->GPR[22], self->GPR[23], self->GPR[24], self->GPR[25], self->GPR[26], self->GPR[27], self->GPR[28], self->GPR[29], self->GPR[30], self->GPR[31], self->FPR[0], self->FPR[1], self->FPR[2], self->FPR[3], self->FPR[4], self->FPR[5], self->FPR[6], self->FPR[7], self->FPR[8], self->FPR[9], self->FPR[10], self->FPR[11], self->FPR[12], self->FPR[13], self->FPR[14], self->FPR[15], self->FPR[16], self->FPR[17], self->FPR[18], self->FPR[19], self->FPR[20], self->FPR[21], self->FPR[22], self->FPR[23], self->FPR[24], self->FPR[25], self->FPR[26], self->FPR[27], self->FPR[28], self->FPR[29], self->FPR[30], self->FPR[31]);
  return;
};

void fetch(simulator *self) {
  self->OP_CODE = self->TEXT[self->PC];
  self->PC++;
  self->COUNT++;
}
