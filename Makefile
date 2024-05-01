CC=clang
CFLAG=-lm -lraylib
CLIB=-L /usr/local/lib/
CINC=-I /usr/local/include/


build:src/main.c
	${CC} ${CINC} -o main src/main.c ${CLIB} ${CFLAG}
	mkdir -p build
	mv main ./build/

clean:
	rm -rf build
