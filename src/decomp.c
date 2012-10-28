//TODO:deal with decompression

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "common.h"
#include "decomp.h"
#include "ppm.h"

void Decompress(char * infile, char * outfile)
{
	unsigned long long l, h, firstQtr, thirdQtr, half;
	int divisor;
	int weights[256+1]; /*first zero + next 256 char elements */
	int aggresivity = DEFAULT_AGGR;
	unsigned long long i;
	char c;
	unsigned long long intervalLenght;

	DFile dataFile = NewFile(outfile, "wb");
	CFile compFile = NewFile(infile, "rb");

	l = 0;
	h = ULLONG_MAX/2;
	intervalLenght = h;
	firstQtr = h/4;
	half = firstQtr*2;
	thirdQtr = firstQtr + half;

	for (i = 0; i<=256; i++)
		weights[i] = i;
	divisor = 256; 
	//debug
	fseek(compFile.desc, -sizeof(long long), SEEK_END);
	fread(&i, sizeof(long long), 1, compFile.desc);
	fseek(compFile.desc, 0, SEEK_SET);
	while (1) {
		
		unsigned char bit = GetBit(&compFile);
		if(!strcmp("eof", compFile.status)) {
			fclose(compFile.desc);
			break;
		}	
		intervalLenght /= 2;
		l = l + bit*(h - l);
		h = l + intervalLenght;
	}
		divisor = RecalcWeight(weights, c, &aggresivity);
		i++;
		if(i%1000000 == 0)
			printf("\n%lld", i);
	}
	printf("\n");
}
