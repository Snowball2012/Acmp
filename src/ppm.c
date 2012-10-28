#include "ppm.h"


int RecalcWeight(int * weights,unsigned char c, int * aggresivity)
{
	int i;
	if (weights[256]>DEFAULT_MAX_SIZE)
		for(i = 0; i<=256; i++) 
			weights[i] /= 2;
	for(i = c; i<=256; i++)
		weights[i] += *aggresivity;
	return weights[256];
}
