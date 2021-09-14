#include "rle.h"

int main (void) {

  int i;
  size_t original_length, compressed_length;
  uint8_t buffer[10] = {0,0,0,0,20,0,0,20,0,0};

  for(i = 0; i < 10; i++) {
    printf("%u ", buffer[i]);
  }
  printf("\n");

  uint8_t *rle_buffer = rle_compress(buffer, sizeof(buffer), &compressed_length);

  printf("Compressed Length: %lu\n", compressed_length);

  for(i = 0; i < compressed_length; i++) { printf("%u ", rle_buffer[i]); }
  printf("\n");


  uint8_t* decode_buffer = rle_decompress(rle_buffer, compressed_length, &original_length);
    for(i = 0; i < 10; i++) {
    printf("%u ", decode_buffer[i]);
  }
  printf("\n");

  free(rle_buffer);
}