/* KLroot.h */

#ifndef _KL_ROOT_H_
#define _KL_ROOT_H_

#define MAXIT 1e4

double drtsafe(void (*funcd)(double, double *, double *), double x1,
	double x2, double xacc);
double drtsafevf(void (*funcd)(double, double *, double *, double *), 
	double *funcparam, double x1, double x2, double xacc);

#endif /* _KL_ROOT_H_ */
