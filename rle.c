#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_REPEATS 255
#define NO_REPEAT_MASK 0x80

char* encode(size_t buffer_size, void *buffer) {

	char *outbuf;
  unsigned long long i, j, k;
  char *buffer_ptr = (char *) buffer;

  outbuf = (char *)calloc(buffer_size, sizeof(char));

  char current_val = buffer_ptr[0];
  j = 0;
  k = 1;
  for(i = 1; i < buffer_size; i++) {
    //printf("i: %llu j: %llu k: %llu, current_val: %u\n", i, j, k, current_val);
    if(buffer_ptr[i] == current_val) {
      k++;
    } else {

      if(j == buffer_size) {
        return(NULL);
      }

      outbuf[j++] = current_val;
      outbuf[j++] = k;
      current_val = buffer_ptr[i];
      k = 1;
    }
  }

  outbuf[j++] = current_val;
  outbuf[j++] = k;

  for(i = 0; i < j; i=i+2) {
    printf("Value: %u Length: %u\n", outbuf[i], outbuf[i+1]);
  }

  return(outbuf);

}

uint8_t* rle_compress(size_t buffer_size, void *buffer) {

  size_t i = 0;
  size_t j = 4; 
  uint8_t k;

  // treat input as a byte array
  uint8_t *buffer_ptr = (uint8_t *) buffer;

  uint8_t *temp_array = (uint8_t *)calloc(buffer_size+4, sizeof(uint8_t));

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

  for(i = 1; i <= 4; i++) {
    temp_array[4-i] = (uint8_t) j>>(8*i);
  }

  return(temp_array);

}


void* rle_decompress( uint8_t *buffer, size_t original_size, size_t compressed_size) {

  uint8_t* temp_array = malloc( original_size * sizeof( uint8_t ) );
  size_t i = 4;
  size_t j = 0;
  uint8_t val, k, count;

  while(i < compressed_size) {
      val = buffer[i++];
      count = buffer[i++];
      for( k = 0; k < count; k++ ) {
        temp_array[j++] = val;
      }
  }

  return( temp_array );

}


int main (void) {

  int i;
  size_t original_length, compressed_length;
  uint8_t buffer[10] = {200,1,1,1,0,0,0,0,0,0};

  for(i = 0; i < 10; i++) {
    printf("%u ", buffer[i]);
  }
  printf("\n");

  uint8_t *rle_buffer = rle_compress(sizeof(buffer), buffer);
  for(i = 0; i < 10; i++) { printf("%u ", rle_buffer[i]); }
  printf("\n");

  // extra compressd length from first 4 bytes
  compressed_length = 
    ((rle_buffer[0] & 0xFF) <<  0) | 
    ((rle_buffer[1] & 0xFF) <<  8) | 
    ((rle_buffer[2] & 0xFF) << 16) | 
    ((rle_buffer[3] & 0xFF) << 24);

  printf("Compressed Length: %lu\n", compressed_length);


  uint8_t* decode_buffer = rle_decompress(rle_buffer, sizeof(buffer), compressed_length);
    for(i = 0; i < 10; i++) {
    printf("%u ", decode_buffer[i]);
  }
  printf("\n");

  free(rle_buffer);
}