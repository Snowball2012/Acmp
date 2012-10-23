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
	char * status;
	char bitIndex;
	char buffer;
};

typedef struct File CFile;
typedef struct File DFile;

#endif 