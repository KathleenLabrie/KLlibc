/* Function: dstddev */
/* Version: 1.0.0 */
/* NR moment with only average and stddev/variance 
 *
 * Needs:
 *   %%%libKLutil%%%
 */

#include <myutil.h>
#include <math.h>

void dstddev(double *datavec, int n, double *ave, double *sdev, double *var)
{
 void nrerror(char error_text[]);
 int j;
 double s,p;

 if (n <= 1) rterror("n must be at least 2 in stddev");
 s=0.0;		/* First pass to get the mean */
 for (j=0;j<n;j++) { s += *(datavec+j);}
 *ave=s/n;
 *var=0;		/* Second pass to get the variance */
 for (j=0;j<n;j++) {
   s=*(datavec+j)-(*ave);
   *var += (p=s*s);
 }
 *var = (*var)/(n-1);
 *sdev = sqrt(*var);	/* Put the pieces together according to the conventional*/
 			/* definitions */
 return;
}
