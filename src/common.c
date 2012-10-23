/*TODO:deal with fopen and char* /int status */
#include <stdio.h>
#include "common.h"


struct File NewFile(char * filename, int status)
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

void WriteByte(char byte, DFile * file)
{
	fwrite(&byte, sizeof(char), 1, file->desc);
	file->buffer = 0;
	file->bitIndex = 0;
}

void FinishWrite(CFile * file)
{
	fwrite(&(file->buffer), sizeof(char), 1, file->desc);
	file->buffer = 0;
	file->bitIndex = 0;
	file->status = CLOSED;
	fclose(file->desc);
	file->desc = NULL;
}
