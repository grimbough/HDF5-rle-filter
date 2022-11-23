#include "rle8/rle8.h"

#define DIM0            5000
#define DIM1            5
#define CHUNK0          5
#define CHUNK1          5

int main (void) {

  int i;
  uint32_t fileSize = DIM0 * sizeof(uint8_t);
  //uint8_t buffer[10] = {0,0,0,0,0,0,0,0,0,0};
  uint8_t *buffer = calloc(DIM0, sizeof(uint8_t));

  for(i = 0; i < 10; i++) {
    printf("%u ", buffer[i]);
  }
  printf("\n");

  // Get Compress Bounds.
  const uint32_t compressedBufferSize = rle8_compress_bounds(fileSize);
  uint8_t *pCompressedData = (uint8_t *)malloc(compressedBufferSize);

  const uint32_t compressedSize = rle8_compress(buffer, fileSize, pCompressedData, compressedBufferSize);

  printf("Compressed Length: %u\n", compressedSize);

  for(i = 0; i < compressedSize; i++) { printf("%u ", pCompressedData[i]); }
  printf("\n");


  // Allocate Output Buffer.
  uint8_t *pDecompressedData = (uint8_t *)malloc(fileSize);

  const uint32_t decompressedSize = rle8_decompress(pCompressedData, compressedSize, pDecompressedData, fileSize);
  for(i = 0; i < 10; i++) {
    printf("%u ", pDecompressedData[i]);
  }
  printf("\n");

  free(pCompressedData);
  free(pDecompressedData);
}
