/* From NR function : mrqcof */
/* Used by mrqmin */
/* y=f(x1,x2,a) */

/* Needs:
 *   %%%KLutil%%%
 */

#include <KLutil.h> 

void dmrqcofD(double **x, double y[], double sig[], int ndim, int ndata, 
	double a[], int ia[], int ma, double **alpha, double beta[], 
	double *chisq,
	void (*funcs)(double [], double [], double *, double [], int, int))
{
 int i,j,k,l,m,mfit=0;
 double ymod,wt,sig2i,dy,*dyda,*point;

 dyda=dvector(ma);
 point=dvector(ndim);
 for (j=0;j<ma;j++) 
 	if (ia[j]) mfit++;
 for (j=0;j<mfit;j++) {	/* Initialize (symmetric) alpha, beta */
   for (k=0;k<=j;k++) alpha[j][k]=0.0;
   beta[j]=0.0;
 }
 *chisq=0.0;
 for (i=0;i<ndata;i++) {	/* Summation loop over all data */
   for (j=0;j<ndim;j++) point[j]=*(*(x+j)+i);
   (*funcs)(point,a,&ymod,dyda,ma,ndim);
   sig2i=1.0/(sig[i]*sig[i]);
   dy=y[i]-ymod;
   for (j=-1,l=0;l<ma;l++) {
     if (ia[l]) {
       wt=dyda[l]*sig2i;
	for (j++,k=-1,m=0;m<=l;m++) 
		if (ia[m]) alpha[j][++k] += wt*dyda[m];
	beta[j] += dy*wt;
     }
   }
   *chisq += dy*dy*sig2i;	/* and find chi square */
 }
 for (j=1;j<mfit;j++)	/* Fill in the symmetric side */
 	for (k=0;k<j;k++) alpha[k][j]=alpha[j][k];
 free_dvector(dyda);
}
