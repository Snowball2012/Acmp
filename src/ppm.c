#include <math.h>
#include "ppm.h"
#define  DW2AGGR_COEF 50.0f


int RecalcWeight(unsigned char c, char mode)
{
	int i,j;
	int * count;
	int * w = weights[prev2][prev].weights;
	if (w[256]>DEFAULT_MAX_SIZE)
		for(i = 1; i<=256; i++) {
			w[i] = w[i]/2;
			if (w[i]%2) {
				w[i]++;
				for(j = i; j <256; j++)
					w[j+1]+=2;
			}
		}
	for(i = c + 1; i<=256; i++)
		w[i] += weights[prev2][prev].aggresivity*(int)(exp((double)mode));
	count = &(weights[prev2][prev].count);
	(*count)++;
	if(*count > 10240){
		RecalcAggr();
		*count = 0;
	}
	PushChar(mode,c);
	return (weights[prev2][prev].weights)[256];
}

int RecalcAggr(void)
{
	double alpha, dw = 0;
	int i;
	Table * t = &(weights[prev2][prev]);
	alpha = (double)t->weights[256]/(double)t->old[256];
	for(i = 1; i<257; i++) {
		t->old[i] *= alpha;
		dw += abs(t->weights[i]-t->weights[i-1] - t->old[i] + t->old[i-1]);
	}
    dw /= (t->weights[256] + t->old[256]);
	for(i = 1; i<257; i++) 
		t->old[i] = t->weights[i];
	t->aggresivity = (int)(sqrt(dw)*DW2AGGR_COEF*DEFAULT_AGGR/t->aggresivity)*2;
	return 0;
}

void InitTable(void)
{
	int i, j, k;
	for (i = 0; i<256; i++)
		for (j = 0; j<256; j++) {
			weights[i][j].count = 0;
			weights[i][j].aggresivity = DEFAULT_AGGR;
			for (k = 0; k<=256; k++) {
				(weights[i][j].old)[k] = k*10*DEFAULT_AGGR;
				(weights[i][j].weights)[k] = k*10*DEFAULT_AGGR;
			}
		}
	prev = 0;
	prev2 = 0;
}

void PushChar(char mode, char c) {
	switch(mode) {
		case 1:
			prev = c;
			break;
		case 2:
			prev2 = prev;
			prev = c;
			break;
		default:
			break;
	}
}










