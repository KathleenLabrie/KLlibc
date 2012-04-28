/* Function : evalfunc */
/* Version: 0.1.0 */
/*   Evaluate a function and output the x and y vectors.  Ndim represents
 *   the number of vectors in x.  For example, ndim is 1 for a XY function.
 *   Ndim would be 2 for a XYZ function (a surface for example).
 *
 *   Some functions are provided in the KLfunc library.
 *
 * int evalfunc(double **x, double *yfit, int ndim, unsigned long ndata, 
 *		double coeff[], int ncoeff, 
 *		void (*func)(double[],double[],double*,double[],int))
 *
 * Calling evalfunc:
 *	status = evalfunc(x,yfit,ndim,ndata,coeff,ncoeff,pfunc);
 *
 *	Note: pfunc is declared as : void (*pfunc)();
 *
 * Needs:
 */

int evalfunc(double **x, double *y, int ndim, unsigned long ndata, 
	double coeff[], int ncoeff, 
	void (*func)(double [], double[] , double *, double [], int))
{
 int status=0,dim;
 unsigned long n;
 double point[ndim],value;
 double junk[ncoeff];
 
 for (n=0; n<ndata; n++) {
   for (dim=0;dim<ndim;dim++) point[dim]=x[dim][n];
   func(point,coeff,&value,junk,ncoeff);
   y[n]=value;
 }

 return(status);
}
