all: 
	gcc -Wall -g src/main.c src/comp.c src/decomp.c src/common.c -o bin/arcp
