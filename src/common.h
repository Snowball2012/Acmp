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
	int status;
	char bitIndex;
	char buffer;
};

typedef struct File CFile;
typedef struct File DFile;

struct File NewFile(char * filename, int status);
char GetSymbol(CFile * file);
void WriteBit(char bit, CFile * file);
void WriteByte(char byte, DFile * file);
void FinishWrite(CFile * file);

#endif 
