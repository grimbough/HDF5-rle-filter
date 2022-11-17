#include "Turbo-Run-Length-Encoding/trle.h"
#include <stdio.h>

int main (void) {

  int i;
  size_t original_length, compressed_length;
  uint8_t buffer[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

  size_t flen = sizeof(buffer);
  int n = flen;
  unsigned char *in  = (unsigned char*)&buffer[0];
  unsigned char *out = (unsigned char*)malloc(flen*4/3+1024);
  unsigned char *cpy = (unsigned char*)malloc(n + 1024);

  for(i = 0; i < flen; i++) {
    printf("%u ", in[i]);
  }
  printf("\n");

  unsigned l = srlec8(in, flen, out, 0xda);

  for(i = 0; i < l; i++) {
    printf("%u ", out[i]);
  }
  printf("\n");

  //trled(out, l, cpy, n);
  srled8(out, l, cpy, n, 0xda);

  for(i = 0; i < n; i++) {
    printf("%u ", cpy[i]);
  }
  printf("\n");

  free(out);
  free(cpy);
  return 0;
}