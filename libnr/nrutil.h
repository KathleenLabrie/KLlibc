#ifndef _NR_UTILS_H_
#define _NR_UTILS_H_

void nrerror(char error_text[]);

float **nr_matrix(long nrl, long nrh, long ncl, long nch);
float ***nr_f3tensor(long nrl, long nrh, long ncl, long nch, long ndl, 
	long ndh);

void nr_free_matrix(float **m, long nrl, long nrh, long ncl, long nch);
void nr_free_f3tensor(float ***t, long nrl, long nrh, long ncl, long nch,
	long ndl, long ndh);

#endif
