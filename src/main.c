#include <stdio.h>
#include "comp.h"
#include "decomp.h"
#include "common.h"

int main(int argc, char ** argv) 
{
	if (argc < 3)
		return 1;
	switch (*argv[1]) {
		case 'c':
			if(argc>3)
				Compress(argv[2], argv[3], argv[4]);
			else
				Compress(argv[2], argv[3], "ari");
			break;
		case 'd':
			Decompress(argv[2], argv[3]);
			break;
		default:
			printf("incorrect option - %c\n", *argv[1]);
			return 1;
			break;
	}
	return 0;
}
