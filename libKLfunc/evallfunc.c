/* Function : evallfunc */
/* Version: 0.1.0 */
/*   Evaluate a linear function and output the x and y vectors.  Ndim represents
 *   the number of vectors in x BUT IS CURRENTLY IGNORED.  For example, ndim is 
 *   1 for a XY function.  Ndim would be 2 for a XYZ function (a surface for 
 *   example).
 *
 *	WORKS ONLY ON LINEAR PROFILES
 *
 *   Some functions are provided in the KLfunc library.
 *
 * int evallfunc(double *x, double *yfit, int ndim, unsigned long ndata, 
 *              double coeff[], int ncoeff, 
 *              void (*func)(double,double[],int))
 *
 * Calling evalfunc:
 *      status = evalfunc(x,yfit,ndim,ndata,coeff,ncoeff,pfunc);
 *
 *      Note: pfunc is declared as : void (*pfunc)();
 *
 * Needs:
 *   %%%libKLutil%%%
 */


#include <myutil.h>

void evallfunc(double *x, double *yfit, int ndim, unsigned long ndata,
	double coeff[], int ncoeff,
	void (*func)(double, double [], int))
/* yfit = coeff0*afunc0 + coeff1*afunc1 + ... + coeff(ncoeff-1)*afunc(ncoeff-1)
*/
{
 int i;
 unsigned long n;
 double *afunc;

 afunc=dvector(ncoeff);
 for (n=0;n<ndata;n++) {
   yfit[n]=0;
   (*func)(x[n],afunc,ncoeff);
   for (i=0;i<ncoeff;i++) yfit[n] += coeff[i]*afunc[i];
 }
 free_dvector(afunc);
 
 return;
}
