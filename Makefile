CC := clang
CFLAG := -lm -lraylib
CLIB := /usr/local/lib/
CINC := /usr/local/include/
target = ./build/

.DEFAULT_GOAL := help

help:
	$(info )
	$(info Usage: make build)
	$(info )
	$(info You can customize the value of CLIB and CINC variables.)
	$(info Example: make build CLIB='-L /path/to/new/lib' CINC='-I /path/to/new/include' -target=pathtotarget)
	$(info or spesify target path : make build -target=/path/to/target )
	$(info )

clean:
	@ls | grep -v 'resource\|src\|Makefile\|.git\|.gitignore\|README.md' | xargs rm -rf
	$(info clean everything)

build: src/main.c clean
	$(info )
	$(info COMPILER : ${CC})
	$(info CFLAG : ${CFLAG})
	$(info CLIB : ${CLIB})
	$(info CINC : ${CINC})
	$(info )

	@${CC} -I ${CINC} -o main src/main.c -L ${CLIB} ${CFLAG}
	@mkdir -p ${target} 
	@cp -r ./resource ${target}
	@mv main ${target}
	@$(info move to : ${target})

