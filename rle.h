#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

uint8_t* rle_compress(void *buffer, size_t buffer_size, size_t *output_size);
void* rle_decompress(uint8_t *buffer, size_t buffer_size, size_t *output_size);