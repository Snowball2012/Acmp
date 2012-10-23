#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "common.h"
#include "comp.h"


void Compress(char * infile, char * outfile)
{
	DFile dataFile = NewFile(infile, O_RDONLY);
	CFile compFile = NewFile(outfile, O_WRONLY|O_CREAT);

}
