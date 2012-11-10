
#include <stdio.h>
#include <string.h>
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
	bit <<= (7-i);
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

void FinishWrite(CFile * file,unsigned long long i, int btf, const char * mode)
{
	char m;
	//if(btf)
		WriteBit(1, file);
	fwrite(&(file->buffer), sizeof(char), 1, file->desc);
	fwrite(&i, sizeof(long long), 1, file->desc);
	if (!strcmp("ari", mode))
		m = 0;
	else if (!strcmp("ppm1", mode))
		m = 1;
	else m = 2;
	fwrite(&m, sizeof(char), 1, file->desc);
	file->buffer = 0;
	file->bitIndex = 0;
	file->status = CLOSED;
	fclose(file->desc);
	file->desc = NULL;
}

unsigned char GetBit(CFile * file)
{
	unsigned char bit;
	char i;
	i = file->bitIndex;
	if (i == 0) {
		fread(&(file->buffer), sizeof(char), 1, file->desc);
		if(feof(file->desc)) {
			bit = 0;
			file->status = "eof";
		}
	}
	bit = 1 << (7-i);
	bit &= file->buffer;
	bit >>= (7-i);
	i++;
	if(i>7)
		i = 0;
	file->bitIndex = i;
	return bit;
}