#include <H5PLextern.h>

#include "rle.h"

static size_t H5Z_filter_rle(unsigned int flags, size_t cd_nelmts,
                     const unsigned int cd_values[], size_t nbytes,
                     size_t *buf_size, void **buf);

#define H5Z_FILTER_RLE 30007

const H5Z_class2_t H5Z_RLE[1] = {{
    H5Z_CLASS_T_VERS,       /* H5Z_class_t version */
    (H5Z_filter_t)H5Z_FILTER_RLE,         /* Filter id number             */
    1,              /* encoder_present flag (set to true) */
    1,              /* decoder_present flag (set to true) */
    "HDF5 Run Length Encoding Filter",
                                /* Filter name for debugging    */
    NULL,                       /* The "can apply" callback     */
    NULL,                       /* The "set local" callback     */
    (H5Z_func_t)H5Z_filter_rle, /* The actual filter function   */
}};

H5PL_type_t H5PLget_plugin_type(void) {return H5PL_TYPE_FILTER;}
const void *H5PLget_plugin_info(void) {return H5Z_RLE;}


static size_t H5Z_filter_rle(unsigned int flags, size_t cd_nelmts,
                     const unsigned int cd_values[], size_t nbytes,
                     size_t *buf_size, void **buf)
{
  char *outbuf = NULL;
  size_t outbuflen, outdatalen;
  int ret;


  if (flags & H5Z_FLAG_REVERSE) {

    /** Decompressing the data **/

    size_t *os_ptr = (size_t *)(*&buf[0]);

    outbuf = rle_decompress(*buf, nbytes, &outbuflen);

    if (outbuf == NULL) {
      fprintf(stderr, "memory allocation failed for rle compression\n");
      goto cleanupAndFail;
    }

    outdatalen = outbuflen;


  } else {

    /** Compressing the data **/

    outbuf = rle_compress(*buf, nbytes, &outbuflen);

    if (outbuf == NULL) {
      fprintf(stderr, "memory allocation failed for rle compression\n");
      goto cleanupAndFail;
    }

    outdatalen = outbuflen;

    fprintf(stdout, "nbytes: %lu outdatalen: %lu\n", nbytes, outdatalen);

  }

  /* Always replace the input buffer with the output buffer. */
  free(*buf);
  *buf = outbuf;
  *buf_size = outbuflen;
  return outdatalen;

  cleanupAndFail:
  if (outbuf)
    free(outbuf);
  return 0;
}