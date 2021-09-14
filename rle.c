#include "rle.h"

#define MAX_REPEATS 255

uint8_t* rle_compress(void *buffer, size_t buffer_size, size_t *output_size) {

  size_t i = 0;
  size_t j = sizeof(size_t); 
  uint8_t k;

  // treat input as a byte array
  uint8_t *buffer_ptr = (uint8_t *) buffer;

  // allocate a buffer to write the endcoded version to
  uint8_t *temp_array = (uint8_t *)calloc(buffer_size+j, sizeof(uint8_t));
  if(!temp_array) {
    return(NULL);
  }

  // write the size of the original buffer in the first 4 bytes
  size_t *size_ptr = (size_t*)(&temp_array[0]);
  *size_ptr = buffer_size;

  while(i < buffer_size) {
    k = 0;
    // record current value
    temp_array[j++] = buffer_ptr[i];
    while( buffer_ptr[i] == temp_array[j-1] &&
           k < MAX_REPEATS &&
           k < buffer_size ) {
      k++;
      i++;
    }

    temp_array[j++] = k;

  }

  *output_size = j;

  return(temp_array);

}


void* rle_decompress(uint8_t *buffer, size_t buffer_size, size_t *output_size ) {

  uint8_t val, k, count;
  size_t i = sizeof(size_t);
  size_t j = 0;
  size_t *os_ptr = (size_t*)(&buffer[0]);
  *output_size = os_ptr[0];

  uint8_t* temp_array = malloc( output_size[0] * sizeof( uint8_t ) );
  if(!temp_array) {
    return(NULL);
  }

  while(i < buffer_size) {
      val = buffer[i++];
      count = buffer[i++];
      for( k = 0; k < count; k++ ) {
        temp_array[j++] = val;
      }
  }

  return( temp_array );

}

