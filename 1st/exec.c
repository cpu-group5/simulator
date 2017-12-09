#include "stdio.h"
#include "stdlib.h"
#include "exec.h"
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

void exec(simulator *self){
  int rs,rt,rd,c,cc,ft,fs,fd,cond,OP;
  OP = self->OP_CODE;
  switch (self->OP) {
    case op_add:
      rs = GET_RS(OP), rt = GET_RT(OP), rd = GET_RD(OP);
      self->GPR[rd] = self->GPR[rs] + self->GPR[rt];
      return;
    case op_addi:
      rs = GET_RS(OP), rt = GET_RT(OP), c = GET_SC(OP);
      self->GPR[rt] = self->GPR[rs] + ((c & 0x8000 ? 0xFFFF0000 : 0) | c);
      return;
    case op_sub:
      rs = GET_RS(OP), rt = GET_RT(OP), rd = GET_RD(OP);
      self->GPR[rd] = self->GPR[rs] - self->GPR[rt];
      return;
    case op_and:
      rs = GET_RS(OP), rt = GET_RT(OP), rd = GET_RD(OP);
      self->GPR[rd] = self->GPR[rs] & self->GPR[rt];
      return;
    case op_andi:
      rs = GET_RS(OP), rt = GET_RT(OP), c = GET_SC(OP);
      self->GPR[rt] = self->GPR[rs] & c;
      return;
    case op_or:
      rs = GET_RS(OP), rt = GET_RT(OP), rd = GET_RD(OP);
      self->GPR[rd] = self->GPR[rs] | self->GPR[rt];
      return;
    case op_ori:
      rs = GET_RS(OP), rt = GET_RT(OP), c = GET_SC(OP);
      self->GPR[rt] = self->GPR[rs] | c;
      return;
    case op_nor:
      rs = GET_RS(OP), rt = GET_RT(OP), rd = GET_RD(OP);
      self->GPR[rd] = ~(self->GPR[rs] | self->GPR[rt]);
      return;
    case op_sll:
      rt = GET_RT(OP), rd = GET_RD(OP), c = GET_SSC(OP);
      self->GPR[rd] = self->GPR[rt] << c;
      return;
    case op_srl:
      rt = GET_RT(OP), rd = GET_RD(OP), c = GET_SSC(OP);
      self->GPR[rd] = self->GPR[rt] >> c;
      return;
    case op_slt:
      rs = GET_RS(OP), rt = GET_RT(OP), rd = GET_RD(OP);
      self->GPR[rd] = self->GPR[rs] <= self->GPR[rt];
      return;
    case op_slti:
      rs = GET_RS(OP), rt = GET_RT(OP), c = GET_SC(OP);
      self->GPR[rt] = self->GPR[rs] <= ((c & 0x8000 ? 0xFFFF0000 : 0) | c);
      return;
    case op_beq:
      rs = GET_RS(OP), rt = GET_RT(OP), c = GET_SC(OP);
      if (self->GPR[rs] == self->GPR[rt]) {
          self->PC += ((c & 0x8000 ? 0xFFFF0000 : 0) | c) - 1;
      }
      return;
    case op_bne:
      rs = GET_RS(OP), rt = GET_RT(OP), c = GET_SC(OP);
      if (self->GPR[rs] != self->GPR[rt]) {
          self->PC += ((c & 0x8000 ? 0xFFFF0000 : 0) | c) - 1;
      }
      return;
    case op_j:
      c = GET_LC(OP);
      self->PC = c;
      return;
    case op_jal:
      c = GET_LC(OP);
      self->GPR[31] = self->PC; // self->PC is already incremented before
      self->PC = c;
      return;
    case op_jr:
      rs = GET_RS(OP);
      self->PC = self->GPR[rs];
      return;
    case op_jalr:
      rs = GET_RS(OP);
      self->GPR[31] = self->PC;
      self->PC = self->GPR[rs];
      return;
    case op_lw:
      rs = GET_RS(OP), rt = GET_RT(OP), c = GET_SC(OP);
      self->GPR[rt] = self->DATA[self->GPR[rs] + c];
      return;
    case op_sw:
      rs = GET_RS(OP), rt = GET_RT(OP), c = GET_SC(OP);
      self->DATA[self->GPR[rs] + c] = self->GPR[rt];
      return;
    case op_in:
      rt = GET_RT(OP);
      exit (1);
      // fread(&self->GPR[rt], 1, 1, stdin);
      return;
    case op_out:
      rt = GET_RT(OP);
      fwrite(&self->GPR[rt], 1, 1, stdout);
      return;
    case op_bt_s:
      cc = GET_BCC(OP), c = GET_SC(OP);
      if (self->FPCC & (1 << cc)) {
          self->PC += ((c & 0x8000 ? 0xFFFF0000 : 0) | c) - 1;
      }
      return;
    case op_bf_s:
      cc = GET_BCC(OP), c = GET_SC(OP);
      if (!(self->FPCC & (1 << cc))) {
          self->PC += ((c & 0x8000 ? 0xFFFF0000 : 0) | c) - 1;
      }
      return;
    case op_add_s:
      ft = GET_FT(OP), fs = GET_FS(OP), fd = GET_FD(OP);
      self->FPR[fd] = self->FPR[fs] + self->FPR[ft];
      return;
    case op_sub_s:
      ft = GET_FT(OP), fs = GET_FS(OP), fd = GET_FD(OP);
      self->FPR[fd] = self->FPR[fs] - self->FPR[ft];
      return;
    case op_mul_s:
      ft = GET_FT(OP), fs = GET_FS(OP), fd = GET_FD(OP);
      self->FPR[fd] = self->FPR[fs] * self->FPR[ft];
      return;
    case op_div_s:
      ft = GET_FT(OP), fs = GET_FS(OP), fd = GET_FD(OP);
      self->FPR[fd] = self->FPR[fs] / self->FPR[ft];
      return;
    case op_c_s:
      ft = GET_FT(OP), fs = GET_FS(OP), cc = GET_CCC(OP), cond = GET_COND(OP);
      self->FPCC |= 1 << cc;
      if (cond == 2) {
          if (!(self->FPR[fs] == self->FPR[ft])) self->FPCC ^= 1 << cc;
      } else if (cond == 12) {
          if (!(self->FPR[fs] < self->FPR[ft])) self->FPCC ^= 1 << cc;
      } else if (cond == 14) {
          if (!(self->FPR[fs] <= self->FPR[ft])) self->FPCC ^= 1 << cc;
      }
      return;
    case op_lw_s:
      rs = GET_RS(OP), ft = GET_FT(OP), c = GET_SC(OP);
      int addr;
	    addr = self->GPR[rs]+c;
	    if (!(0 <= addr && addr < 0x80000)) {
		    fprintf(stderr, "overflow: trying to lw_s from %X\n", addr);
        exit(1);
        return;
	    }
	    self->FPR[ft] = *((float*)&self->DATA[addr]);
	    return;
    case op_sw_s:
      rs = GET_RS(OP), ft = GET_FT(OP), c = GET_SC(OP);
	    addr = self->GPR[rs]+c;
      if (!(0 <= addr && addr < 0x80000)) {
        fprintf(stderr, "overflow: trying to sw_s to %X\n", addr);
        exit(1);
        return;
      }
	    *((float*)&self->DATA[addr]) = self->FPR[ft];
	    return;
    case op_lui:
      rt = GET_RT(OP), c = GET_SC(OP);
      self->GPR[rt] = ((uint32_t)c) << 16;
      return;
    case op_mov_s:
      ft = GET_FT(OP), fd = GET_FD(OP);
      self->FPR[fd] = self->FPR[ft];
      return;
    case op_neg_s:
      ft = GET_FT(OP), fd = GET_FD(OP);
      self->FPR[fd] = -self->FPR[ft];
      return;
    case op_ftoi:
      rt = GET_RT(OP), fs = GET_FS(OP);
      self->GPR[rt] = lrintf(self->FPR[fs]);
      return;
    case op_itof:
      ft = GET_FT(OP), rs = GET_RS(OP);
      self->FPR[ft] = (float) ((int32_t)self->GPR[rs]);
      return;
  }
};
