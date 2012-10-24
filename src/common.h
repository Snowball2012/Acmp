/* Functions for common use 
 * 1.File operations
 * 2.smth else
 */

#ifndef COMMON_H
#define COMMON_H

#define CLOSED 0
#define READ 1
#define WRITE 2

struct File {
	char * name;
	FILE * desc;
	const char * status;
	char bitIndex;
	char buffer;
};

typedef struct File CFile;
typedef struct File DFile;

struct File NewFile(char * filename, const char * status);
unsigned char GetSymbol(DFile * file);
void WriteBit(unsigned char bit, CFile * file);
void WriteByte(unsigned char byte, DFile * file);
void FinishWrite(CFile * file);

#endif 
