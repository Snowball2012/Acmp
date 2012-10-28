
#include <stdio.h>
#include "common.h"


struct File NewFile(char * filename, const char * status)
{
	struct File file;
	file.name = filename;
	file.status = status;
	file.bitIndex = 0;
	file.buffer = 0;
	file.desc = fopen(filename, status);
	if (!file.desc)
		printf("\nNULL POINTER!!!!!!\n");
	return file;
}

unsigned char GetSymbol(CFile * file)
{
	unsigned char c;
	fread(&c, sizeof(char), 1, file->desc);
	if(feof(file->desc)) {
		c = 0;
		file->status = "eof";
	}
	return c;
}

void WriteBit(unsigned char bit, CFile * file)
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

void WriteByte(unsigned char byte, DFile * file)
{
	fwrite(&byte, sizeof(char), 1, file->desc);
	file->buffer = 0;
	file->bitIndex = 0;
}

void FinishWrite(CFile * file,unsigned long long i)
{
	fwrite(&(file->buffer), sizeof(char), 1, file->desc);
	fwrite(&i, sizeof(long long), 1, file->desc);
	file->buffer = 0;
	file->bitIndex = 0;
	file->status = CLOSED;
	fclose(file->desc);
	file->desc = NULL;
}

unsigned char GetBit(CFile * file)
{
	char bit;
	char i;
	i = file->bitIndex;
	bit &= file->buffer;
	i++;
	if(i>7){
		i = 0;
		fread(&(file->buffer), sizeof(char), 1, file->desc);
		if(feof(file->desc)) {
			bit = 0;
			file->status = "eof";
		}
		file->buffer = 0;
	}
	file->bitIndex = i;
	bit <<= i;
	return bit;
}