
LIBNAME=libsimdcomp.a

all: $(LIBNAME)


HEADERS=./include/simdbitpacking.h ./include/simdcomputil.h ./include/simdintegratedbitpacking.h ./include/simdcomp.h ./include/simdfor.h ./include/avxbitpacking.h ./include/avx512bitpacking.h

OBJECTS= simdbitpacking.o simdintegratedbitpacking.o simdcomputil.o \
		 simdpackedsearch.o simdpackedselect.o simdfor.o avxbitpacking.o avx512bitpacking.o

$(LIBNAME): $(OBJECTS)
	$(AR) cq $(LIBNAME) $(OBJECTS)


avx512bitpacking.o: ./src/avx512bitpacking.c $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/avx512bitpacking.c -Iinclude

avxbitpacking.o: ./src/avxbitpacking.c $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/avxbitpacking.c -Iinclude

simdfor.o: ./src/simdfor.c $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/simdfor.c -Iinclude

simdcomputil.o: ./src/simdcomputil.c $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/simdcomputil.c -Iinclude

simdbitpacking.o: ./src/simdbitpacking.c $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/simdbitpacking.c -Iinclude

simdintegratedbitpacking.o: ./src/simdintegratedbitpacking.c  $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/simdintegratedbitpacking.c -Iinclude

simdpackedsearch.o: ./src/simdpackedsearch.c $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/simdpackedsearch.c -Iinclude

simdpackedselect.o: ./src/simdpackedselect.c $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/simdpackedselect.c -Iinclude


clean:
	rm -f $(OBJECTS) $(LIBNAME) 
