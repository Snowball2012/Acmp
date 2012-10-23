//TODO:write functions for tables and ppm

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "common.h"
#include "comp.h"


void Compress(char * infile, char * outfile)
{
	unsigned long long l, h, divisor, firstQtr, thirdQtr, half;
	l = 0;
	h = ULLONG_MAX;
	divisor = 
	DFile dataFile = NewFile(infile, "r");
	CFile compFile = NewFile(outfile, "w");
	while (!feof(dataFile.desc)) {
	}

}
