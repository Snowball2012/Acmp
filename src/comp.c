//TODO:Compression done. For now...
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
	long long i;

	DFile dataFile = NewFile(infile, "rb");
	CFile compFile = NewFile(outfile, "wb");

	l = 0;
	h = ULLONG_MAX/2;
	firstQtr = h/4;
	half = firstQtr*2;
	thirdQtr = firstQtr + half;

	for (i = 0; i<=256; i++)
		weights[i] = i;
	divisor = 256; 
	//debug
	i = 0;
	while (1) {
		
		unsigned char c = GetSymbol(&dataFile);
		unsigned long long old_l, old_h;
		int btf = 0;  /* bits to follow */
		if(!strcmp("eof", dataFile.status)) {

			fclose(dataFile.desc);
			FinishWrite(&compFile, i);
			break;
		}	
		old_l = l;
		old_h = h;
		l = old_l + (old_h-old_l + 1)*((double)weights[c-1]/(double)divisor);
		h = old_l + (old_h-old_l + 1)*((double)weights[c]/(double)divisor) - 1 ;      
		
		for (;;) {  /* Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn (,;,;,) */
			if (h < half)
				BitPlusFollow(0, &compFile, btf);
			else if (l >= half) {
				BitPlusFollow(1, &compFile, btf);
				l-=half;
				h-=half;
			} else if (l >= firstQtr && h < thirdQtr) {
				btf++;
				l-=firstQtr;
				h-=firstQtr;
			} else 
				break;
			l+=l;
			h+=h+1;
		}
		divisor = RecalcWeight(weights, c, &aggresivity);
		i++;
		if(i%1000000 == 0)
			printf("\n%lld", i);
	}
	printf("\n");
}
