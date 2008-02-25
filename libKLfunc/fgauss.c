/* Function : fgauss */
/*   Gaussian profile, f(x).  For dmrqmin. */

/* ndim not used. ndim=2 for profiles */

#include <math.h>

/*void fgauss(double x, double a[], double *y, double dyda[], int na, int ndim)
*/
void fgauss(double x[], double a[], double *y, double dyda[], int na)
{
 double ex, arg;


 arg=x[0]-a[2];
 ex=exp( -0.5*( (arg*arg)/(a[3]*a[3]) ) );
 *y=a[1]*ex + a[0];
 dyda[0]=1;
 dyda[1]=ex;
 dyda[2]=a[1]*ex*arg/(a[3]*a[3]);
 dyda[3]=a[1]*ex*(arg*arg)/pow(a[3],3);

 return;
}
