#ifndef PPM_H
#define PPM_H

#define DEFAULT_AGGR 50
#define DEFAULT_MAX_SIZE 650000

typedef struct {
	int weights[257];
	int old[257];
	int count;
	int divisor;
	int aggresivity;
	int oldAgr;
} Table;


Table weights[256][256];
unsigned char prev;
unsigned char prev2;

void InitTable(void);
void PushChar(char mode, char c);

int RecalcWeight (unsigned char c,char mode);
int RecalcAggr (void);

#endif