#include "ppm.h"


int RecalcWeight(int * weights,unsigned char c, int * aggresivity)
{
	if (weights[255]>DEFAULT_MAX_SIZE)
		for(; c<=255; c++) 
			weights[c] /= 2;
	for(; c<=255; c++)
		weights[c] += *aggresivity;
	return weights[255];
}
