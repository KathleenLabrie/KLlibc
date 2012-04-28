/* KLfunc.h */

#ifndef _KL_FUNC_H_
#define _KL_FUNC_H_

#define FUNC_GAUSS_PROFILE 101
#define FUNC_MOFFAT_PROFILE 102
#define FUNC_POLYNOME_PROFILE 103

#define FUNC_GAUSS_SURFACE 201
#define FUNC_MOFFAT_SURFACE 202
/*#define FUNC_POLYNOME_SURFACE 203*/

#define NCOEFF_GAUSS_PROFILE 4
#define NCOEFF_MOFFAT_PROFILE 5
#define NCOEFF_GAUSS_SURFACE 6
#define NCOEFF_MOFFAT_SURFACE 7

/* *********** Special Functions ************** */
float factrl(int n);
float gammln(float xx);
float gammq(float a, float x);
void gcf(float *gammcf, float a, float x, float *gln);
void gser(float *gamser, float a, float x, float *gln);

/* ************* Profiles, f(x) *************** */

/* Gaussian Profile: f(x) = A*exp(-0.5 * ((x-x0)/sigma)^2) + S
 *			a[0] = S  (constant) 
 *			a[1] = A
 *			a[2] = x0
 *			a[3] = sigma */
void fgauss(double x, double a[], double *y, double dyda[], int na);
/*void fmoffat(double x, double a[], double *y, double dyda[], int na);*/

/* Polynomial Profile: f(x) = sum( a_i * x^i )  [ 0 < i < na ] */
void fpolynome(double x, double afunc[], int na);

/* *********** Surfaces, f(x1,x2) ************* */

/* Gaussian Surface: 
 *	f(x1,x2) = A*exp(-0.5 * ( ((x1-x10)/sig1)^2 + ((x2-x20)/sig2)^2 )) + S
 *			a[0] = S 
 *			a[1] = A
 *			a[2] = x10
 *			a[3] = x20
 *			a[4] = sig1
 *			a[5] = sig2 */
void fgaussS(double x[], double a[], double *y, double dyda[], int na);

/* Moffat Surface:
 *	f(x1,x2) = A*( 1 + ((x1-x10)/alphaX1)^2 + ((x2-x20)/alphaX2)^2 )^beta + S
 *			a[0] = S
 *			a[1] = A
 *			a[2] = x10
 *			a[3] = x20
 *			a[4] = beta
 *			a[5] = alphaX1
 *			a[6] = alphaX2 */
void fmoffatS(double x[], double a[], double *y, double dyda[], int na);


/************************ Utilities ****************************/

/* Evaluate a function */
int evalfunc(double **x, double *yfit, int ndim, unsigned long ndata,
	double coeff[], int ncoeff, 
	void (*func)(double [], double[] , double *, double [], int));

int evallfunc(double *x, double *yfit, int ndim, unsigned long ndata,
	double coeff[], int ncoeff,
	void (*func)(double, double[], int));

#endif /* _KL_FUNC_H_ */
