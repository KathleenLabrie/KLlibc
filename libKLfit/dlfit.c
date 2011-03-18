/* NR function : lfit */
/* Version: 1.0.1 */
/* General Least Square Fit 
 *
 * Needs:
 *   %%%libKLutil%%%
 *   %%%libKLlinear%%%
 */

#include "./KLfit.h"		/* for dcovsrt */
#include <myutil.h>
#include <KLlinear.h>	/* for dgaussj */
#include <stdio.h>

void dlfit(double x[], double y[], double sig[], int ndat, double a[], int ia[],
	int ma, double **covar, double *chisq, 
	void (*funcs)(double, double [], int))
{
 int i,j,k,l,m,mfit=0;
 double ym,wt,sum,sig2i,**beta,*afunc;
 int junk;

 beta=dmatrix(ma,1);
 afunc=dvector(ma);
 for (j=0;j<ma;j++)
 	if (ia[j]) mfit++;
 if (mfit == 0) rterror("lfit: no parameters to be fitted");
 for (j=0;j<mfit;j++) {
   for (k=0;k<mfit;k++) covar[j][k]=0.0;
   beta[j][0]=0.0;
 }
 for (i=0;i<ndat;i++) {
   (*funcs)(x[i],afunc,ma);
   ym=y[i];
   if (mfit < ma) {
     for (j=0;j<ma;j++)
     	if (!ia[j]) ym -= a[j]*afunc[j];
   }
   sig2i=1.0/SQR(sig[i]);
   for (j=-1,l=0;l<ma;l++) {
     if (ia[l]) {
       wt = afunc[l]*sig2i;
	for (j++,k=-1,m=0;m<=l;m++)
		if (ia[m]) covar[j][++k] += wt*afunc[m];
	beta[j][0] += ym*wt;
     }
   }
 }
 for (j=1;j<mfit;j++)
 	for (k=0;k<j;k++)
		covar[k][j]=covar[j][k];
 dgaussj(covar,mfit,beta,1);
 for (j=-1,l=0;l<ma;l++)
 	if (ia[l]) a[l]=beta[++j][0];
 *chisq=0.0;
 for (i=0;i<ndat;i++) {
   (*funcs)(x[i],afunc,ma);
   for (sum=0.0,j=0;j<ma;j++) sum += a[j]*afunc[j];
   *chisq += SQR((y[i]-sum)/sig[i]);
 }
 dcovsrt(covar,ma,ia,mfit);
 free_dvector(afunc);
 free_dmatrix(beta);

}
