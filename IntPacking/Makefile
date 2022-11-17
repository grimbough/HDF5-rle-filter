all: lbp libH5Zlbp.so h5ex_d_lbp sdc h5ex_d_sdc libH5Zsimdcomp.so h5ex_d_sdc

h5ex_d_sdc: h5ex_d_simdcomp.c libH5Zsimdcomp.so
	$(CC) h5ex_d_simdcomp.c \
	-I'/mnt/data/R-lib/4.1.1-bioc_3.14/Rhdf5lib/include' \
	-L'/mnt/data/R-lib/4.1.1-bioc_3.14/Rhdf5lib/lib' -lhdf5 -lsz -lz -lm -ldl \
	-o h5ex_d_sdc

h5ex_d_lbp: h5ex_d_lbp.c libH5Zlbp.so
	$(CC) h5ex_d_lbp.c \
	-I'/mnt/data/R-lib/4.1.1-bioc_3.14/Rhdf5lib/include' \
	-L'/mnt/data/R-lib/4.1.1-bioc_3.14/Rhdf5lib/lib' -lhdf5 -lsz -lz -lm -ldl \
	-o h5ex_d_lbp

libH5Zsimdcomp.so: simdcomp/libsimdcomp.a H5Zsimdcomp.c
	$(CC) -fPIC -shared H5Zsimdcomp.c \
	-I./simdcomp/include -I'/mnt/data/R-lib/4.1.1-bioc_3.14/Rhdf5lib/include' \
	-L'/mnt/data/R-lib/4.1.1-bioc_3.14/Rhdf5lib/lib' \
	simdcomp/libsimdcomp.a -o libH5Zsimdcomp.so

libH5Zlbp.so: LittleIntPacker/libLBP.a H5Zlbp.c
	$(CC) -fPIC -shared H5Zlbp.c \
	-I./LittleIntPacker/include -I'/mnt/data/R-lib/4.1.1-bioc_3.14/Rhdf5lib/include' \
	-L'/mnt/data/R-lib/4.1.1-bioc_3.14/Rhdf5lib/lib' \
	./LittleIntPacker/libLBP.a -o libH5Zlbp.so

sdc: simdcomp/libsimdcomp.a main_simdcomp.c
	$(CC) main_simdcomp.c -Isimdcomp/include simdcomp/libsimdcomp.a -o sdc

lbp: LittleIntPacker/libLBP.a main.c
	$(CC) main.c -I./LittleIntPacker/include/ ./LittleIntPacker/libLBP.a -o lbp 

simdcomp/libsimdcomp.a:
	$(MAKE) -C simdcomp

LittleIntPacker/libLBP.a:
	$(MAKE) -C LittleIntPacker

clean:
	$(MAKE) -C simdcomp clean
	$(MAKE) -C LittleIntPacker clean
	rm -f *.o lbp