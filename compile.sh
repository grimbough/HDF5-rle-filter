AR=ar
RANLIB=ranlib

cd /home/msmith/Projects/HDF5-rle-filter
rm *.o *.so librle.a

 

gcc -fPIC -c rle.c
$(AR) cq librle.a rle.o

gcc -fPIC -shared H5Zrle.c -o libH5Zrle.so -I'/mnt/data/R-lib/4.1.1-bioc_3.14/Rhdf5lib/include' librle.a

rm h5ex_d_rle
gcc h5ex_d_rle.c -o h5ex_d_rle -I'/mnt/data/R-lib/4.1.1-bioc_3.14/Rhdf5lib/include' -L'/mnt/data/R-lib/4.1.1-bioc_3.14/Rhdf5lib/lib' -lhdf5 -lsz -lz -lm -ldl 

./h5ex_d_rle
