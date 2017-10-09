#include <stdio.h>

int main(int argc, char const *argv[]) {
  FILE *in_fp;
  FILE *out_fp;
  unsigned char buffer[8];
  unsigned char binary_buffer[1];
  unsigned char op_binary_buffer[4];
  int i = 0;
  int j = 0;
  in_fp = fopen("input.txt", "r");
  out_fp = fopen("out.dat", "wb");
  while (fread(buffer,sizeof(buffer),1,in_fp)){
    binary_buffer[0] &= 0;
    for (i = 0; i < 8; i++) {
      buffer[0] = buffer[i]- 48;
      // fwrite(buffer,1,1,out_fp); // write 10 bytes from our buffer
      printf("Start\n");
      printf("i is %d\n",i);
      printf("%d\n",buffer[0]);
      printf("%08X\n",buffer[0] << (7-i));
      binary_buffer[0] |= (buffer[0] << (7-i));

      printf("%08X\n",binary_buffer[0]);
    }
    op_binary_buffer[j] = binary_buffer[0];
      printf("End\n");
      // printf("%08X\n",binary_buffer[0]);
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
  // for (i = 0; i < 4; i++) {
  //   binary_buffer[i] =
  //   fread(buffer,sizeof(buffer),1,in_fp); // read 10 bytes to our buffer
  //   printf("%s\n", );
  //   fwrite(buffer,sizeof(buffer),1,out_fp); // write 10 bytes from our buffer
  // }
  return 0;
}
