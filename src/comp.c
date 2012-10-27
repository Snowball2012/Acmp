//TODO:deal with weights array, i need first zero elem

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "common.h"
#include "comp.h"
#include "ppm.h"


void Compress(char * infile, char * outfile)
{
	unsigned long long l, h, firstQtr, thirdQtr, half;
	int divisor;
	int weights[256+1]; /*first zero + next 256 char elements */
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

	while (true) {
		unsigned char c = GetSymbol(&dataFile);
		int old_l, old_h;
		if(strcmp("eof", dataFile.status)) {
			fclose(dataFile.desc);
			FinishWrite(&compFile);
			break;
		}	
		old_l = l;
		old_h = h;
		l = old_l + weights[c-1]*(old_h-old_l + 1)/divisor;
		h = old_l + weights[c]*(old_h-old_l + 1)/divisor - 1;          
		for (;;) {  /* Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn (,;,;,) */
			

	}

}
