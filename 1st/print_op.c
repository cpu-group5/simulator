#include "stdio.h"
#include "stdlib.h"
#include "simulator.h"
void print_op(simulator *self){
    int rs,rt,rd,c,cc,ft,fs,fd,cond,OP;
    OP = self->OP_CODE;
    switch (self->OP) {
      case op_add:
          rs = GET_RS(OP), rt = GET_RT(OP), rd = GET_RD(OP);
        	fprintf(stderr, "add\t%%r%d, %%r%d, %%r%d\n", rd, rs, rt);
      	  return;
      case op_addi:
          rs = GET_RS(OP), rt = GET_RT(OP), c = GET_SC(OP);
        	fprintf(stderr, "addi\t%%r%d, %%r%d, %d\n", rt, rs, c);
      	  return;
      case op_sub:
          rs = GET_RS(OP), rt = GET_RT(OP), rd = GET_RD(OP);
        	fprintf(stderr, "sub\t%%r%d, %%r%d, %%r%d\n", rd, rs, rt);
      	  return;
      case op_and:
          rs = GET_RS(OP), rt = GET_RT(OP), rd = GET_RD(OP);
        	fprintf(stderr, "and\t%%r%d, %%r%d, %%r%d\n", rd, rs, rt);
      	  return;
      case op_andi:
          rs = GET_RS(OP), rt = GET_RT(OP), c = GET_SC(OP);
        	fprintf(stderr, "andi\t%%r%d, %%r%d, %d\n", rt, rs, c);
      	  return;
      case op_or:
          rs = GET_RS(OP), rt = GET_RT(OP), rd = GET_RD(OP);
        	fprintf(stderr, "or\t%%r%d, %%r%d, %%r%d\n", rd, rs, rt);
      	  return;
      case op_ori:
          rs = GET_RS(OP), rt = GET_RT(OP), c = GET_SC(OP);
        	fprintf(stderr, "ori\t%%r%d, %%r%d, %d\n", rt, rs, c);
      	  return;
      case op_nor:
          rs = GET_RS(OP), rt = GET_RT(OP), rd = GET_RD(OP);
        	fprintf(stderr, "nor\t%%r%d, %%r%d, %%r%d\n", rd, rs, rt);
      	  return;
      case op_sll:
          rt = GET_RT(OP), rd = GET_RD(OP), c = GET_SSC(OP);
        	fprintf(stderr, "sll\t%%r%d, %%r%d, %d\n", rd, rt, c);
      	  return;
      case op_srl:
          rt = GET_RT(OP), rd = GET_RD(OP), c = GET_SSC(OP);
        	fprintf(stderr, "srl\t%%r%d, %%r%d, %d\n", rd, rt, c);
      	  return;
      case op_slt:
          rs = GET_RS(OP), rt = GET_RT(OP), rd = GET_RD(OP);
        	fprintf(stderr, "slt\t%%r%d, %%r%d, %%r%d\n", rd, rs, rt);
      	  return;
      case op_slti:
          rs = GET_RS(OP), rt = GET_RT(OP), c = GET_SC(OP);
        	fprintf(stderr, "slti\t%%r%d, %%r%d, %d\n", rt, rs, c);
      	  return;
      case op_beq:
          rs = GET_RS(OP), rt = GET_RT(OP), c = GET_SC(OP);
        	fprintf(stderr, "beq\t%%r%d, %%r%d, %d\n", rs, rt, c);
      	  return;
      case op_bne:
          rs = GET_RS(OP), rt = GET_RT(OP), c = GET_SC(OP);
        	fprintf(stderr, "bne\t%%r%d, %%r%d, %d\n", rs, rt, c);
      	  return;
      case op_j:
          c = GET_LC(OP);
        	fprintf(stderr, "j\t%d\n", c);
      	  return;
      case op_jal:
          c = GET_LC(OP);
        	fprintf(stderr, "jal\t%d\n", c);
      	  return;
      case op_jr:
          rs = GET_RS(OP);
        	fprintf(stderr, "jr\t%%r%d\n", rs);
      	  return;
      case op_jalr:
          rs = GET_RS(OP);
        	fprintf(stderr, "jalr\t%%r%d\n", rs);
      	  return;
      case op_lw:
          rs = GET_RS(OP), rt = GET_RT(OP), c = GET_SC(OP);
        	fprintf(stderr, "lw\t%%r%d, %d(%%r%d)\n", rt, c, rs);
      	  return;
      case op_sw:
          rs = GET_RS(OP), rt = GET_RT(OP), c = GET_SC(OP);
        	fprintf(stderr, "sw\t%%r%d, %d(%%r%d)\n", rt, c, rs);
      	  return;
      case op_in:
          rt = GET_RT(OP);
        	fprintf(stderr, "in\t%%r%d\n", rt);
      	  return;
      case op_out:
          rt = GET_RT(OP);
        	fprintf(stderr, "out\t%%r%d\n", rt);
      	  return;
      case op_bt_s:
          cc = GET_BCC(OP), c = GET_SC(OP);
        	fprintf(stderr, "bt.s\t%d, %d\n", cc, c);
      	  return;
      case op_bf_s:
          cc = GET_BCC(OP), c = GET_SC(OP);
        	fprintf(stderr, "bf.s\t%d, %d\n", cc, c);
      	  return;
      case op_add_s:
          ft = GET_FT(OP), fs = GET_FS(OP), fd = GET_FD(OP);
        	fprintf(stderr, "add.s\t%%f%d, %%f%d, %%f%d\n", fd, fs, ft);
      	  return;
      case op_sub_s:
          ft = GET_FT(OP), fs = GET_FS(OP), fd = GET_FD(OP);
        	fprintf(stderr, "sub.s\t%%f%d, %%f%d, %%f%d\n", fd, fs, ft);
      	  return;
      case op_mul_s:
          ft = GET_FT(OP), fs = GET_FS(OP), fd = GET_FD(OP);
        	fprintf(stderr, "mul.s\t%%f%d, %%f%d, %%f%d\n", fd, fs, ft);
      	  return;
      case op_div_s:
          ft = GET_FT(OP), fs = GET_FS(OP), fd = GET_FD(OP);
        	fprintf(stderr, "div.s\t%%f%d, %%f%d, %%f%d\n", fd, fs, ft);
      	  return;
      case op_c_s:
          ft = GET_FT(OP), fs = GET_FS(OP), cc = GET_CCC(OP), cond = GET_COND(OP);
          self->FPCC |= 1 << cc;
          if (cond == 2) {
          	fprintf(stderr, "c.eq.s\t%d, %%f%d, %%f%d\n", cc, fs, ft);
          } else if (cond == 12) {
          	fprintf(stderr, "c.lt.s\t%d, %%f%d, %%f%d\n", cc, fs, ft);
          } else if (cond == 14) {
          	fprintf(stderr, "c.le.s\t%d, %%f%d, %%f%d\n", cc, fs, ft);
          }
        return;
      case op_lw_s:
          rs = GET_RS(OP), ft = GET_FT(OP), c = GET_SC(OP);
        	fprintf(stderr, "lw.s\t%%f%d, %d(%%r%d)\n", ft, c, rs);
      	  return;
      case op_sw_s:
          rs = GET_RS(OP), ft = GET_FT(OP), c = GET_SC(OP);
        	fprintf(stderr, "sw.s\t%%f%d, %d(%%r%d)\n", ft, c, rs);
      	  return;
      case op_lui:
          rt = GET_RT(OP), c = GET_SC(OP);
        	fprintf(stderr, "lui\t%%r%d, %d\n", rt, c);
      	  return;
      case op_mov_s:
          ft = GET_FT(OP), fd = GET_FD(OP);
        	fprintf(stderr, "mov.s\t%%f%d, %%f%d\n", fd, ft);
      	  return;
      case op_neg_s:
          ft = GET_FT(OP), fd = GET_FD(OP);
        	fprintf(stderr, "neg.s\t%%f%d, %%f%d\n", fd, ft);
      	  return;
      case op_abs_s:
          ft = GET_FT(OP), fd = GET_FD(OP);
        	fprintf(stderr, "abs.s\t%%f%d, %%f%d\n", fd, ft);
      	  return;
      case op_sqrt_s:
          ft = GET_FT(OP), fd = GET_FD(OP);
        	fprintf(stderr, "sqrt.s\t%%f%d, %%f%d\n", fd, ft);
      	  return;
      case op_ftoi:
          rt = GET_RT(OP), fs = GET_FS(OP);
        	fprintf(stderr, "ftoi\t%%r%d, %%f%d\n", rt, fs);
      	  return;
      case op_itof:
          ft = GET_FT(OP), rs = GET_RS(OP);
        	fprintf(stderr, "itof\t%%f%d, %%r%d\n", ft, rs);
      	  return;
    }
}
