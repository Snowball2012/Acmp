//TODO:deal with weights array, i need first zero elem

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "common.h"
#include "comp.h"
#include "ppm.h"

void BitPlusFollow (unsigned char bit, CFile * file, int bits2Follow) {
	WriteBit(bit, file);
	for(;bits2Follow>0; bits2Follow--)
		WriteBit(!bit, file);
}

void Compress(char * infile, char * outfile)
{
	unsigned long long l, h, firstQtr, thirdQtr, half;
	int divisor;
	int weights[256+1]; /*first zero + next 256 char elements */
	int aggresivity = DEFAULT_AGGR;
	int i;

	DFile dataFile = NewFile(infile, "r");
	CFile compFile = NewFile(outfile, "w");

	l = 0;
	h = ULLONG_MAX;
	firstQtr = h/4;
	half = firstQtr*2;
	thirdQtr = firstQtr + half;

	for (i = 0; i<=256; i++)
		weights[i] = i;
	divisor = 256; 

	while (1) {
		unsigned long long qtr; 
		unsigned char c = GetSymbol(&dataFile);
		unsigned long long old_l, old_h;
		int btf = 0;  /* bits to follow */
		if(strcmp("eof", dataFile.status)) {
			fclose(dataFile.desc);
			FinishWrite(&compFile);
			break;
		}	
		old_l = l;
		old_h = h;
		l = old_l + weights[c-1]*(old_h-old_l + 1)/divisor;
		h = old_l + weights[c]*(old_h-old_l + 1)/divisor - 1;      
		qtr = (h-l)/4;
		firstQtr = l + qtr;
		half = firstQtr + qtr;
		thirdQtr = half + qtr;
		for (;;) {  /* Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn (,;,;,) */
			if (h < half)
				BitPlusFollow(0, &compFile, btf);
			else if (l > half) {
				BitPlusFollow(1, &compFile, btf);
				l-=(qtr*2);
				h-=(qtr*2);
			} else if (l >= firstQtr && h < thirdQtr) {
				btf++;
				l-=qtr;
				h-=qtr;
			} else 
				break;
			l+=l;
			h+=h+1;
		}
		divisor = RecalcWeight(weights, c, &aggresivity);
	}
}
