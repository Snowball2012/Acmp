//TODO:Decompression is strange

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "common.h"
#include "decomp.h"
#include "ppm.h"

extern int oldTable[257];

void Decompress(char * infile, char * outfile)
{
	unsigned long long l, h, firstQtr, thirdQtr, half;
	int divisor;
	
	unsigned long long i;
	unsigned char c;
	unsigned long long value;
	int j;
	char mode;

	DFile dataFile = NewFile(outfile, "wb");
	CFile compFile = NewFile(infile, "rb");

	l = 0;
	h = 0x1000000000000;
	firstQtr = h/4;
	half = firstQtr*2;
	thirdQtr = firstQtr + half;

	InitTable();
	divisor = (weights[0][0].weights)[256]; 
	//debug
	fseek(compFile.desc, -((long)(sizeof(long long)+sizeof(char))), SEEK_END);
	fread(&i, sizeof(long long), 1, compFile.desc);
	fread(&mode, sizeof(char), 1, compFile.desc);
	fseek(compFile.desc, 0, SEEK_SET);
	value = 0;
	for (j = 0; j<48; j++)
		value +=value + GetBit(&compFile);
	while (1) {
		unsigned long long old_l, old_h;
		/*seek for c*/

		for (c = 255; (h-l)*(weights[prev2][prev].weights)[c] > (value-l)*divisor; c--);
		
		old_l = l;
		old_h = h;
		l = old_l + (old_h-old_l + 1)*(weights[prev2][prev].weights)[c]/divisor;
		h = old_l + (old_h-old_l + 1)*(weights[prev2][prev].weights)[c+1]/divisor-1;  
		for (;;) { /* Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn (,;,;,) */
			if (h < half)
				;
			else if (l >= half) {
				l-=half;
				h-=half;
				value -=half;
			} else if (l >= firstQtr && h < thirdQtr) {
				value-=firstQtr;
				l-=firstQtr;
				h-=firstQtr;
			} else break;
			l+=l;
			h+=h+1;
			value+=value+GetBit(&compFile);
		}	
		WriteByte(c, &dataFile);
		divisor = RecalcWeight(c,mode);
		i--;
		if(i == 0){
			fclose(dataFile.desc);
			fclose(compFile.desc);
			break;
		}
		if(i == 1) {
			l+=l;
			h+=h;
			value+=value+GetBit(&compFile);
			firstQtr += firstQtr;
			half+=half;
			thirdQtr+=thirdQtr;
		}
	}
	printf("\n");
}
