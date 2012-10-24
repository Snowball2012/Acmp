//TODO:deal with weights array, i need first zero elem

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "common.h"
#include "comp.h"
#include "ppm.h"


void Compress(char * infile, char * outfile)
{
	unsigned long long l, h, firstQtr, thirdQtr, half;
	int divisor;
	int weights[256];
	int i;
	DFile dataFile = NewFile(infile, "r");
	CFile compFile = NewFile(outfile, "w");
	l = 0;
	h = ULLONG_MAX;
	firstQtr = h/4;
	half = firstQtr*2;
	thirdQtr = firstQtr + half;

	for (i = 0; i<256; i++)
		weights[i] = i+1;
	divisor = 256; 
	while (!feof(dataFile.desc)) {
		unsigned char c = GetSymbol(&dataFile);
		int old_l, old_h;
		old_l = l;
		old_h = h;
		l = old_l + weights[c-1];
	}

}
