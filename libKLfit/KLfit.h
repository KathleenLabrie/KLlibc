/* KLfit.h */

#ifndef _KL_FIT_H_
#define _KL_FIT_H_

void dcovsrt(double **covar, int ma, int ia[], int mfit);
void dlfit(double x[], double y[], double sig[], int ndat, double a[], int ia[],
	int ma, double **covar, double *chisq, 
	void (*funcs)(double, double [], int));
void dlfitg(double *x, double *y, double *sig, int ndat, double *a, int *ia, 
	int ma, double *chisq, void (*funcs)(double, double [], int));
void dmrqcofD(double **x, double y[], double sig[], int ndim, int ndata,
	double a[], int ia[], int ma, double **alpha, double beta[],
	double *chisq,
	void (*funcs)(double [], double [], double *, double [], int, int));
void dmrqminD(double **x, double y[], double sig[], int ndim, int ndata,
	double a[], int ia[], int ma, double **covar, double **alpha,
	double *chisq,
	void (*funcs)(double [], double [], double *, double [], int, int),
	double *alamda);

#endif /* _KL_FIT_H_ */
