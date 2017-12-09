#include <stdio.h>
#include <stdlib.h>
#include "decoder.h"
#define R_MASK 0xFC00003F
#define IJ_MASK 0xFC000000
#define FL_MASK 0xFFE00000

void init_decoder(decoder *self){
  self->decode = decode;
};

enum OP decode(decoder *self, uint32_t OP_CODE){
  if ((OP_CODE & R_MASK) == 0x00000020) {
    printf("%s\n", "op_add");
    printf("%s\n", "op_add");
    return op_add;
  } else if ((OP_CODE & IJ_MASK) == 0x20000000) {
    printf("%s\n", "op_addi");
    return op_addi;
  } else if ((OP_CODE & R_MASK) == 0x00000022) {
    printf("%s\n", "op_sub");
    return op_sub;
  } else if ((OP_CODE & R_MASK) == 0x00000024) {
    printf("%s\n", "op_and");
    return op_and;
  } else if ((OP_CODE & IJ_MASK) == 0x30000000) {
    printf("%s\n", "op_andi");
    return op_andi;
  } else if ((OP_CODE & R_MASK) == 0x00000025) {
    printf("%s\n", "op_or");
    return op_or;
  } else if ((OP_CODE & IJ_MASK) == 0x34000000) {
    printf("%s\n", "op_ori");
    return op_ori;
  } else if ((OP_CODE & R_MASK) == 0x00000027) {
    printf("%s\n", "op_nor");
    return op_nor;
  } else if ((OP_CODE & R_MASK) == 0x00000000) {
    printf("%s\n", "op_sll");
    return op_sll;
  } else if ((OP_CODE & R_MASK) == 0x00000002) {
    printf("%s\n", "op_srl");
    return op_srl;
  } else if ((OP_CODE & R_MASK) == 0x0000002A) {
    printf("%s\n", "op_slt");
    return op_slt;
  } else if ((OP_CODE & IJ_MASK) == 0x28000000) {
    printf("%s\n", "op_slti");
    return op_slti;
  } else if ((OP_CODE & IJ_MASK) == 0x10000000) {
    printf("%s\n", "op_beq");
    return op_beq;
  } else if ((OP_CODE & IJ_MASK) == 0x14000000) {
    printf("%s\n", "op_bne");
    return op_bne;
  } else if ((OP_CODE & IJ_MASK) == 0x08000000) {
    printf("%s\n", "op_j");
    return op_j;
  } else if ((OP_CODE & IJ_MASK) == 0x0C000000) {
    printf("%s\n", "op_jal");
    return op_jal;
  } else if ((OP_CODE & R_MASK) == 0x00000008) {
    printf("%s\n", "op_jr");
    return op_jr;
  } else if ((OP_CODE & R_MASK) == 0x00000009) {
    printf("%s\n", "op_jalr");
    return op_jalr;
  } else if ((OP_CODE & IJ_MASK) == 0x8C000000) {
    printf("%s\n", "op_lw");
    return op_lw;
  } else if ((OP_CODE & IJ_MASK) == 0xAC000000) {
    printf("%s\n", "op_sw");
    return op_sw;
  } else if ((OP_CODE & IJ_MASK) == 0x68000000) {
    printf("%s\n", "op_in");
    return op_in;
  } else if ((OP_CODE & IJ_MASK) == 0x6C000000) {
    printf("%s\n", "op_out");
    return op_out;
  } else if ((OP_CODE & (FL_MASK | 0x00030000)) == 0x45010000) {
    printf("%s\n", "op_bt_s");
    return op_bt_s;
  } else if ((OP_CODE & (FL_MASK | 0x00030000)) == 0x45000000) {
    printf("%s\n", "op_bf_s");
    return op_bf_s;
  } else if ((OP_CODE & (FL_MASK | 0x0000003F)) == 0x46000000) {
    printf("%s\n", "op_add_s");
    return op_add_s;
  } else if ((OP_CODE & (FL_MASK | 0x0000003F)) == 0x46000001) {
    printf("%s\n", "op_sub_s");
    return op_sub_s;
  } else if (
        (OP_CODE & (FL_MASK | 0x0000003F)) == 0x46000002) {
    printf("%s\n", "op_mul_s");
    return op_mul_s;
  } else if ((OP_CODE & (FL_MASK | 0x0000003F)) == 0x46000003) {
    printf("%s\n", "op_div_s");
    return op_div_s;
  } else if ((OP_CODE & (FL_MASK | 0x00000030)) == 0x46000030) {
    printf("%s\n", "op_c_s");
    return op_c_s;
  } else if ((OP_CODE & IJ_MASK) == 0xC4000000) {
    printf("%s\n", "op_lw_s");
    return op_lw_s;
  } else if ((OP_CODE & IJ_MASK) == 0xE4000000) {
    printf("%s\n", "op_sw_s");
    return op_sw_s;
  } else if ((OP_CODE & IJ_MASK) == 0x3C000000) {
    printf("%s\n", "op_lui");
    return op_lui;
  } else if ((OP_CODE & (FL_MASK | 0x0000003F)) == 0x46000006) {
    printf("%s\n", "op_mov_s");
    return op_mov_s;
  } else if ((OP_CODE & (FL_MASK | 0x0000003F)) == 0x46000007) {
    printf("%s\n", "op_neg_s");
    return op_neg_s;
  } else if ((OP_CODE & IJ_MASK) == 0xD0000000) {
    printf("%s\n", "op_ftoi");
    return op_ftoi;
  } else if ((OP_CODE & IJ_MASK) == 0xC0000000) {
    printf("%s\n", "op_itof");
    return op_itof;
  } else{
    printf("%s: %08X", "undefined OP_CODE", OP_CODE);
    return undefined;
  }
};
