#include <math.h>
#include "stdio.h"
#include "stdlib.h"
#include "simulator.h"

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
      self->GPR[rd] = (int32_t)self->GPR[rs] <= (int32_t)self->GPR[rt];
      return;
    case op_slti:
      rs = GET_RS(OP), rt = GET_RT(OP), c = GET_SC(OP);
      self->GPR[rt] = (int32_t)self->GPR[rs] <= (int32_t)c;
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
    	int inp;
      inp = getc(self->IFILE);
      if (inp == EOF) {
        fprintf(stderr, "finished");  
        exit (1);
      }
      *((unsigned char*)&self->GPR[rt]) = (unsigned char) inp;
      return;
    case op_out:
      rt = GET_RT(OP);
      // fprintf(stderr, "out is: %8X\n", self->GPR[rt]);
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
    case op_abs_s:
      ft = GET_FT(OP), fd = GET_FD(OP);
      self->FPR[fd] = (self->FPR[ft] < 0) ? -self->FPR[ft] : self->FPR[ft];
      return;
    case op_sqrt_s:
      ft = GET_FT(OP), fd = GET_FD(OP);
      self->FPR[fd] = (float)sqrt((double)self->FPR[ft]);
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
