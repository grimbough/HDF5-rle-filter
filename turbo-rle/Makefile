all: trle libH5Ztrle.so h5ex_d_trle

h5ex_d_trle: h5ex_d_trle.c libH5Ztrle.so
	$(CC) h5ex_d_trle.c \
	-I'/mnt/data/R-lib/4.1.1-bioc_3.14/Rhdf5lib/include' \
	-L'/mnt/data/R-lib/4.1.1-bioc_3.14/Rhdf5lib/lib' -lhdf5 -lsz -lz -lm -ldl \
	-o h5ex_d_trle

libH5Ztrle.so: Turbo-Run-Length-Encoding/libtrle.a H5Ztrle.c
	$(CC) -fPIC -shared H5Ztrle.c \
	-I./Turbo-Run-Length-Encoding/ -I'/mnt/data/R-lib/4.1.1-bioc_3.14/Rhdf5lib/include' \
	-L'/mnt/data/R-lib/4.1.1-bioc_3.14/Rhdf5lib/lib' \
	./Turbo-Run-Length-Encoding/libtrle.a -o libH5Ztrle.so

trle: Turbo-Run-Length-Encoding/libtrle.a main.c
	$(CC) main.c ./Turbo-Run-Length-Encoding/libtrle.a -o trle 

Turbo-Run-Length-Encoding/libtrle.a:
	$(MAKE) -C Turbo-Run-Length-Encoding

clean:
	$(MAKE) -C Turbo-Run-Length-Encoding clean
	rm -f *.o trle