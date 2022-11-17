#include "simdcomp.h"
#include <stdio.h>

int main (void) {

  int i, bit, howmanybytes;
  __m128i * endofbuf;
  size_t j = sizeof(size_t);
  size_t original_size;
  
  uint32_t data[] = {0,0,0,0,0,32,0,0,0,0,8,8,14,1};
  int length = sizeof(data) / sizeof(data[0]);
  size_t N = sizeof(data);



  for(i = 0; i < length; i++) {
    printf("%u ", data[i]);
  }
  printf("\n");

  bit = maxbits_length(data, length);

  uint32_t c = simdpack_compressedbytes(length, bit);
  printf("length: %u bit: %u c: %u\n", length, bit, c);

  // allocate a buffer to write the encoded version to
  uint8_t  *buffer = malloc((sizeof(uint8_t) * c) + j + 1);

  // write the size of the original data in the first bytes
  size_t *size_ptr = (size_t*)(&buffer[0]);
  uint8_t *data_ptr = (uint8_t*)(&buffer[j]);
  *data_ptr = bit;
  data_ptr++;

  *size_ptr = length;

  endofbuf = simdpack_length(data, length, (__m128i *)data_ptr, bit);
  howmanybytes = (endofbuf-(__m128i *)data_ptr)*sizeof(__m128i);

  printf("howmanybytes: %u\n", howmanybytes);


  for(i = 0; i < (c + j); i++) {
    printf("%u ", buffer[i]);
  }
  printf("\n");

  /* DECOMPRESSING */

  original_size = size_ptr[0];
  uint32_t *backdata = (uint32_t *)malloc(original_size * sizeof(uint32_t) );
  
  simdunpack_length((const __m128i *)data_ptr, length, backdata, bit);

  for(i = 0; i < length; i++) {
    printf("%u ", backdata[i]);
  }
  printf("\n");

  free(buffer);
  free(backdata);

  return 0;
}