#include <H5PLextern.h>
#include "bitpacking.h"

static size_t H5Z_filter_lbp(unsigned int flags, size_t cd_nelmts,
                     const unsigned int cd_values[], size_t nbytes,
                     size_t *buf_size, void **buf);

#define H5Z_FILTER_LBP 30009

const H5Z_class2_t H5Z_LBP[1] = {{
    H5Z_CLASS_T_VERS,       /* H5Z_class_t version */
    (H5Z_filter_t)H5Z_FILTER_LBP,         /* Filter id number             */
    1,              /* encoder_present flag (set to true) */
    1,              /* decoder_present flag (set to true) */
    "HDF5 Turbo Run Length Encoding Filter",
                                /* Filter name for debugging    */
    NULL,                       /* The "can apply" callback     */
    NULL,                       /* The "set local" callback     */
    (H5Z_func_t)H5Z_filter_lbp, /* The actual filter function   */
}};

H5PL_type_t H5PLget_plugin_type(void) {return H5PL_TYPE_FILTER;}
const void *H5PLget_plugin_info(void) {return H5Z_LBP;}


static size_t H5Z_filter_lbp(unsigned int flags, size_t cd_nelmts,
                     const unsigned int cd_values[], size_t nbytes,
                     size_t *buf_size, void **buf)
{

  size_t outdatasize;
  int ret;
  int bit = cd_values[0];
  int offset = sizeof(size_t);
  int length;
  char *outbuf, *inbuf;

  if (flags & H5Z_FLAG_REVERSE) {

    /** Decompressing the data **/
    size_t *size_ptr = (size_t*)(*&buf[0]);
    uint8_t *data_ptr = (uint8_t*)(*&buf[0]);
    data_ptr += offset;

    /* size is in bytes, length is number of array elements */
    outdatasize = size_ptr[0];
    length = outdatasize / sizeof(uint32_t);
/*
    fprintf(stdout, "length: %u buf_size: %lu outdatasize: %lu\n", length, *buf_size, outdatasize);
*/
    uint32_t *backdata = malloc(outdatasize * sizeof(uint32_t) + 64 * sizeof(uint32_t) );
    if (backdata == NULL) {
      fprintf(stderr, "memory allocation failed for rle compression\n");
      goto cleanupAndFail;
    }

    inbuf = (char *)(*&buf[0]);
/*
    printf("inbuf: ");
    for(int i = 0; i<nbytes;i++) { printf("%hhu ", inbuf[i]); }
      printf("\n");

    printf("data_ptr: ");
    for(int i = 0; i<nbytes-offset;i++) { printf("%hhu ", data_ptr[i]); }
      printf("\n");
*/
    turbounpack32(data_ptr, length, bit, backdata);
/*
    printf("backdata: ");
    for(int i = 0; i<length;i++) { printf("%u ", backdata[i]); }
    printf("\n");
*/
    outbuf = (char *)&backdata[0];



  } else {

    /** Compressing the data **/

    /* we expect 32-bit ints, so cast buf to that */
    uint32_t *input = (uint32_t *)(*&buf[0]);

    length = nbytes / sizeof(uint32_t);
    outdatasize = byte_count(length, bit);
/*
    for(int i = 0; i<length;i++) { printf("%u ", input[i]); }
    printf("\n");
*/
    //fprintf(stdout, "length: %lu buf_size: %lu outdatasize: %lu\n", length, *buf_size, outdatasize);


    // allocate a buffer to write the encoded version to
    uint8_t  *buffer = malloc((sizeof(uint8_t) * outdatasize) + offset + 32);
    if (buffer == NULL) {
      fprintf(stderr, "memory allocation failed for rle compression\n");
      goto cleanupAndFail;
    }

    size_t *size_ptr = (size_t*)(&buffer[0]);
    uint8_t *data_ptr = (uint8_t*)(&buffer[offset]);

    *size_ptr = nbytes;

    //printf("Size Ptr: %lu\n", size_ptr[0]);

    outdatasize += offset;

    turbopack32(input, length, bit, data_ptr);

    outbuf = (char *)&buffer[0];
/*
    for(int i = 0; i<outdatasize;i++) { printf("%hhu ", outbuf[i]); }
      printf("\n");
*/
  }

  /* Always replace the input buffer with the output buffer. */
  free(*buf);
  *buf = outbuf;
  *buf_size = outdatasize;
  return outdatasize;

  cleanupAndFail:
  if (outbuf)
    free(outbuf);
  return 0;
}