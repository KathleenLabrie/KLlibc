/* KLsort.h */

#ifndef _KL_SORT_H_
#define _KL_SORT_H_

unsigned long dclean(unsigned long n, double a[]);
double dselect(unsigned long k, unsigned long n, double arr[]);
int dvitable(double vmain[], unsigned long nmain, double vec[], 
		unsigned long nvec, double index[]);
void dshell(unsigned long n, double a[]);
void ipiksrt(int n, int arr[]);
void sort2_vecmatrix(unsigned long n, float vec[], float *mat[], int dim);

#endif		/* _KL_SORT_H */
