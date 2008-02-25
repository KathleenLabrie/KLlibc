/* Function : fmoffatS */
/*   Moffat surface, f(x1,x2).  For dmrqminS. */

/* ndim not used. Technically should be 3 for a surface */

#include <math.h>

/* void fmoffatS(double x[], double a[], double *y, double dyda[], int na, 
	int ndim) */
void fmoffatS(double x[], double a[], double *y, double dyda[], int na)
{
 double brackett, arg1, arg2, arg3;

 arg1 = (x[0]-a[2])/a[5];
 arg2 = (x[1]-a[3])/a[6];
 brackett = 1 + arg1*arg1 + arg2*arg2;
 arg3 = -2.*a[1]*a[4]*pow(brackett,a[4]-1);
 *y = a[0] + a[1]*pow(brackett,a[4]);
 dyda[0] = 1;
 dyda[1] = (*y - a[0])/a[1];
 dyda[2] = arg3 * arg1/a[5];
 dyda[3] = arg3 * arg2/a[6];
 dyda[4] = (*y - a[0]) * log(brackett);
 dyda[5] = arg3 * arg1*arg1/a[5];
 dyda[6] = arg3 * arg2*arg2/a[6];

 return;
}
