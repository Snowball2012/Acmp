all: 
	gcc -Wall -g src/main.c src/comp.c src/decomp.c src/common.c src/ppm.c -o bin/arcp
