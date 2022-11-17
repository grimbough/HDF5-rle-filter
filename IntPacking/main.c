#include "bitpacking.h"
#include <stdio.h>

int main (void) {

  int i;
  int bit = 6;
  size_t j = sizeof(size_t);
  size_t original_size;
  
  uint32_t data[10] = {0,0,0,0,0,32,0,0,0,0};
  int length = sizeof(data) / sizeof(data[0]);
  size_t N = sizeof(data);



  for(i = 0; i < length; i++) {
    printf("%u ", data[i]);
  }
  printf("\n");

  uint32_t c = byte_count(length, bit);
  printf("j: %lu c: %u\n", j, c);

  // allocate a buffer to write the encoded version to
  uint8_t  *buffer = malloc((sizeof(uint8_t) * c) + j + 32);

  // write the size of the original data in the first bytes
  size_t *size_ptr = (size_t*)(&buffer[0]);
  uint8_t *data_ptr = (uint8_t*)(&buffer[j]);

  *size_ptr = N;
  turbopack32(data, length, bit, data_ptr);

  for(i = 0; i < (c + j); i++) {
    printf("%u ", buffer[i]);
  }
  printf("\n");

  original_size = size_ptr[0];
  uint32_t *backdata = malloc(original_size * sizeof(uint32_t) + 64 * sizeof(uint32_t) );
  printf("Here\n");
  turbounpack32(data_ptr, length, bit, backdata);

  for(i = 0; i < length; i++) {
    printf("%u ", backdata[i]);
  }
  printf("\n");

  free(buffer);
  free(backdata);

  return 0;
}