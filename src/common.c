/*TODO:FINISH FinishWrite*/
#include <stdio.h>
#include "common.h"


struct File NewFile(const char * filename, char * status)
{
	struct File file;
	file.name = filename;
	file.status = status;
	file.bitIndex = 0;
	file.buffer = 0;
	file.desc = fopen(filename, status);
	return file;
}

char GetSymbol(CFile * file)
{
	char c;
	fread(&c, sizeof(char), 1, file->desc);
	return c;
}

void WriteBit(char bit, CFile * file)
{
	char i;
	i = file->bitIndex;
	bit >>= i;
	file->buffer |= bit;
	i++;
	if(i>7){
		i = 0;
		fwrite(&(file->buffer), sizeof(char), 1, file->desc);
		file->buffer = 0;
	}
	file->bitIndex = i;
}

/* TODO:FINISH FinishWrite */

void FinishWrite
