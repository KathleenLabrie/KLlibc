/* Function: drtsafevf */
/*   From NR's rtsafe */
/*  Using a combination of Newton-Raphson and bisection, find the root
 *  of a function bracketed between x1 and x2.  The root, returned as
 *  the function value drtsafe, will be refined until its accuracy is 
 *  known within +/-xacc.  funcd is a user-supplied routine that
 *  return both the function value and the first derivative of the
 *  function.
 *
 *  [d]rtsafe[vf] : d-> double precision, vf-> variable function
 */

#include "./KLroot.h"
#include <KLutil.h>	/* for rterror, DEBUG */
#include <stdio.h>	/* for gcc4.0, printf */
#include <math.h>

double drtsafevf(void (*funcd)(double, double *, double *, double *), 
	double *funcparam, double x1, double x2, double xacc)
{
 int j,FLAGS;
 double df,dx,dxold,f,fh,fl;
 double temp,xh,xl,rts;

 FLAGS=0;
 /* FLAGS |= 1 << DEBUG; */

 (*funcd)(x1,funcparam,&fl,&df);
 (*funcd)(x2,funcparam,&fh,&df);
 if (FLAGS & 1<<DEBUG) { printf("f(%g)=%g     f(%g)=%g\n",x1,fl,x2,fh); }
 if ((fl > 0.0 && fh > 0.0) || (fl < 0.0 && fh < 0.0))
 	rterror("Root must be bracketed in rtsafe");
 if (fl == 0.0) return x1;
 if (fh == 0.0) return x2;
 if (fl < 0.0) {
    xl=x1;
    xh=x2;
 } else {
    xh=x1;
    xl=x2;
 }
 rts = 0.5*(x1+x2);
 dxold = fabs(x2-x1);
 dx = dxold;
 (*funcd)(rts,funcparam,&f,&df);
 if (FLAGS & 1<<DEBUG) { printf("f(%g)=%g  df(%g)=%g\n",rts,f,rts,df); }
 for (j=1; j<=MAXIT; j++) {
    if ((((rts-xh)*df-f)*((rts-xl)*df-f) >= 0.0)
    	|| (fabs(2.0*f) > fabs(dxold*df))) {
       dxold=dx;
       dx=0.5*(xh-xl);
       rts=xl+dx;
       if (xl == rts) return rts;
    } else {
       dxold=dx;
       dx=f/df;
       temp=rts;
       rts -= dx;
       if (temp == rts) return rts;
    }
    if (fabs(dx) < xacc) return rts;
    (*funcd)(rts,funcparam,&f,&df);
    if (f < 0.0)
       xl=rts;
    else
       xh=rts;
 }
 rterror("Maximum number of iterations exceeded in rtsafe");
 return 0.0;
}
