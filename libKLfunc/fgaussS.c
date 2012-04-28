/* Function : fgaussS */
/*   Gaussian surface, f(x1,x2).  For dmrqminS. */

/* ndim not used. ndim=3 for surfaces */

#include <math.h>

void fgaussS(double x[], double a[], double *y, double dyda[], int na, int ndim)
{
 double ex, arg1, arg2;

 arg1=x[1]-a[2];
 arg2=x[1]-a[3];
 ex=exp( -0.5*( (arg1*arg1)/(a[4]*a[4]) + (arg2*arg2)/(a[5]*a[5]) ) );
 *y=a[1]*ex + a[0];
 dyda[0]=1;
 dyda[1]=ex;
 dyda[2]=a[1]*ex*arg1/(a[4]*a[4]);
 dyda[3]=a[1]*ex*arg2/(a[5]*a[5]);
 dyda[4]=a[1]*ex*(arg1*arg1)/pow(a[4],3);
 dyda[5]=a[1]*ex*(arg2*arg2)/pow(a[5],3);

 return;
}
