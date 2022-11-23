all: rle8 libH5Zrle8.so h5ex_d_rle8

h5ex_d_rle8: h5ex_d_rle8.c libH5Zrle8.so
	$(CC) h5ex_d_rle8.c \
	-I'/mnt/data/R-lib/4.2-bioc_3.16/Rhdf5lib/include' \
	-L'/mnt/data/R-lib/4.2-bioc_3.16/Rhdf5lib/lib' -lhdf5 -lsz -lz -lm -ldl \
	-o h5ex_d_rle8

libH5Zrle8.so: rle8/librle8.a H5Zrle8.c
	$(CC) -fPIC -shared H5Zrle8.c \
	-Irle8/ -I'/mnt/data/R-lib/4.2-bioc_3.16/Rhdf5lib/include' \
	-L'/mnt/data/R-lib/4.2-bioc_3.16/Rhdf5lib/lib' \
	rle8/librle8.a -o libH5Zrle8.so

main: rle8/librle8.a main.c
	$(CC) main.c rle8/librle8.a -o main 

rle8/rle8.a:
	$(MAKE) -C rle8

clean:
	$(MAKE) -C rle8 clean
	rm -f *.o 