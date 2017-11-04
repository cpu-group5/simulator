#ifndef __DECODER_H__
#define __DECODER_H__

#include <stdint.h>
enum OP { op_add, op_addi, op_sub, op_and, op_andi, op_or, op_ori, op_nor, op_sll, op_srl, op_slt, op_slti, op_beq, op_bne, op_j, op_jal, op_jr, op_jalr, op_lw, op_sw, op_in, op_out, op_bt_s, op_bf_s, op_add_s, op_sub_s, op_mul_s, op_div_s, op_inv_s, op_c_s, op_lw_s, op_sw_s, op_lui, op_mov_s, op_neg_s, undefined};
typedef struct decoder{
  void (*init_decoder)(struct decoder *self);
  enum OP (*decode)(struct decoder *self, uint32_t OP_CODE);
} decoder;
enum OP decode(decoder *self, uint32_t OP_CODE);
void init_decoder(decoder *self);

#endif
