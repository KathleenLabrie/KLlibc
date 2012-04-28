/* Function : dchstwo */
/* Version : 1.0.0 */
/*   From NR.  0-offset arrays.
 *
 * Given the array bins1[0..nbins-1] and bins2[0..nbins-1], containing
 * two sets of binned data, and given the number of constraints knstrn
 * (normally 1 or 0), this routine returns the number of degrees of
 * freedom df, the chi-square chsq, and the significance prob.  A small
 * value of prob indicates a significant difference between the 
 * distributions bins1 and bins2.  Note that bins1 and bins2 are both
 * double arrays, although they will normally contain integer values.
 *
 * Calling dchstwo
 *  chstwo(bins1,bins2,nbins,knstrn,&df,&chsq,&prob);
 *
 * Needs:
 *   %%%libKLfunc%%%
 */

#include <KLfunc.h>

void dchstwo(double bins1[], double bins2[], int nbins, int knstrn,
	double *df, double *chsq, double *prob)
{
 int j;
 double temp;
 
 *df=nbins-knstrn;
 *chsq=0.0;
 for (j=0;j<nbins;j++)
    if (bins1[j] == 0.0 && bins2[j] == 0.0)
       --(*df);
    else {
       temp = bins1[j]-bins2[j];
       *chsq += temp*temp/(bins1[j]+bins2[j]);
    }
 *prob=gammq(0.5*(*df),0.5*(*chsq));
}
