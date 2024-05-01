CC := clang
CFLAG := -lm -lraylib
CLIB := /usr/local/lib/
CINC := /usr/local/include/

.DEFAULT_GOAL := help

help:
	$(info )
	$(info Usage: make build)
	$(info )
	$(info You can customize the value of CLIB and CINC variables.)
	$(info Example: make build CLIB='-L /path/to/new/lib' CINC='-I /path/to/new/include')
	$(info )

clean:
	rm -rf build

build: src/main.c clean
	$(info )
	$(info COMPILER : ${CC})
	$(info CFLAG : ${CFLAG})
	$(info CLIB : ${CLIB})
	$(info CINC : ${CINC})
	$(info )

	${CC} -I ${CINC} -o main src/main.c -L ${CLIB} ${CFLAG}
	mkdir -p build
	cp -r ./resource ./build
	mv main ./build

run: build
	./build/main
