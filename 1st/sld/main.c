#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[]) {
  FILE *in_fp;
  FILE *out_fp;
  in_fp = fopen("contest.sld", "r");
  out_fp = fopen("sld.dat", "wb");
  int i;
  float f;
  for (int j = 0; j < 9; j++) {
    if(fscanf(in_fp, "%f", &f) != 1){
      printf("failed to read an float\n");
      exit(1);
    }
    printf("%f\n",f);
    fwrite(&f,4,1,out_fp);
  }
  for (int j = 0; j < 17; j++) {
    for (int k = 0; k < 4; k++) {
      if(fscanf(in_fp, "%d", &i) != 1){
        printf("failed to read an int\n");
        exit(1);
      }
      printf("%d\n",i);
      fwrite(&i,4,1,out_fp);
    }
    for (int k = 0; k < 12; k++) {
      if(fscanf(in_fp, "%f", &f) != 1){
        printf("failed to read an float\n");
        exit(1);
      }
      printf("%f\n",f);
      fwrite(&f,4,1,out_fp);
    }
  }
  for (int j = 0; j < 44; j++) {
    if(fscanf(in_fp, "%d", &i) != 1){
      printf("failed to read an int\n");
      exit(1);
    }
    printf("%d\n",i);
    fwrite(&i,4,1,out_fp);
  }
  // printf("%d\n",i);
  fclose(out_fp);
  return 0;
}
