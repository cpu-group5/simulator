#include <stdio.h>

int main(int argc, char const *argv[]) {
  FILE *in_fp;
  FILE *out_fp;
  unsigned char buffer[8];
  unsigned char binary_buffer[1];
  unsigned char op_binary_buffer[4];
  int i = 0;
  int j = 0;
  in_fp = fopen(argv[1], "r");
  out_fp = fopen(argv[2], "wb");
  while (fread(buffer,sizeof(buffer),1,in_fp)){
    binary_buffer[0] &= 0;
    for (i = 0; i < 8; i++) {
      buffer[0] = buffer[i]- 48;
      binary_buffer[0] |= (buffer[0] << (7-i));

    }
    op_binary_buffer[j] = binary_buffer[0];
      if (j == 3 ) {
        fwrite(op_binary_buffer+3,1,1,out_fp); // write 10 bytes from our buffer
        fwrite(op_binary_buffer+2,1,1,out_fp); // write 10 bytes from our buffer
        fwrite(op_binary_buffer+1,1,1,out_fp); // write 10 bytes from our buffer
        fwrite(op_binary_buffer,1,1,out_fp); // write 10 bytes from our buffer
        j = 0;
      }else{
        j += 1;
      }
  }
  return 0;
}
