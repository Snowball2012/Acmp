//TODO:Compression done. For now...
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "common.h"
#include "comp.h"
#include "ppm.h"

extern int oldTable[257];

void BitPlusFollow (unsigned char bit, CFile * file, int * bits2Follow) {
	WriteBit(bit, file);
	for(;*bits2Follow>0; (*bits2Follow)--)
		WriteBit(!bit, file);
}

void Compress(char * infile, char * outfile, const char * mode)
{
	unsigned long long l, h, firstQtr, thirdQtr, half;
	int divisor;
	char m;
	long long i;
	int btf = 0; /*bits to follow*/
	unsigned char prev = 0;
	DFile dataFile = NewFile(infile, "rb");
	CFile compFile = NewFile(outfile, "wb");

	if (!strcmp("ari", mode))
		m = 0;
	else if (!strcmp("ppm1", mode))
		m = 1;
	else m = 2;

	l = 0;
	h = 0x1000000000000;
	firstQtr = h/4;
	half = firstQtr*2;
	thirdQtr = firstQtr + half;

	InitTable(); 
	divisor = (weights[0][0].weights)[256];
	//debug
	i = 0;
	while (1) {
		
		unsigned char c = GetSymbol(&dataFile);
		unsigned long long old_l, old_h;
		if(!strcmp("eof", dataFile.status)) {

			fclose(dataFile.desc);
			FinishWrite(&compFile, i, btf, mode);
			break;
		}	
		old_l = l;
		old_h = h;
		l = old_l + (old_h-old_l + 1)*(weights[prev2][prev].weights)[c]/(weights[prev2][prev].weights)[256];
		h = old_l + (old_h-old_l + 1)*(weights[prev2][prev].weights)[c+1]/(weights[prev2][prev].weights)[256]-1;      
		
		for (;;) {  /* Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn (,;,;,) */
			if (h < half)
				BitPlusFollow(0, &compFile, &btf);
			else if (l >= half) {
				BitPlusFollow(1, &compFile, &btf);
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
		divisor = RecalcWeight(c,m);
		i++;
		if(i%1000000==0)
			printf("%lld\n",i);
	}
}
