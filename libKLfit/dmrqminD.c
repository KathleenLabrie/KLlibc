/* From NR function : mrqmin */
/* Levenberg-Marquardt Method for Nonlinear Models */
/* y = f(x1,x2,a) */

/* **x => x[ndim-1][ndata] */
/* last int of funcs is ndim */

/* Needs:
 *   %%%KLutil%%%
 *   %%%KLlinear%%%
 */

#include <KLutil.h>
#include <KLlinear.h>

void dmrqminD(double **x, double y[], double sig[], int ndim, int ndata, 
	double a[], int ia[], int ma, double **covar, double **alpha, 
	double *chisq,
	void (*funcs)(double [], double [], double *, double[], int, int), 
	double *alamda)
{
 int j,k,l,m;
 static int mfit;
 static double ochisq,*atry,*beta,*da,**oneda;
   
 if (*alamda < 0.0) {	/* Initialization */
   atry = dvector(ma);
   beta = dvector(ma);
   da = dvector(ma);
   for (mfit=0,j=0;j<ma;j++) if (ia[j]) mfit++;
   oneda=dmatrix(mfit,1);
   *alamda=0.001;
   dmrqcofD(x,y,sig,ndim,ndata,a,ia,ma,alpha,beta,chisq,funcs);
   ochisq=(*chisq);
   for (j=0;j<ma;j++)  atry[j]=a[j];
 }
 for (j=-1,l=0;l<ma;l++) {	/*alter linearized fitting matrix, by augmenting diagonal elements */
   if (ia[l]) {
     for (j++,k=-1,m=0;m<ma;m++) {
       if (ia[m]) {
	  k++;
	  covar[j][k]=alpha[j][k];
	}
     }
     covar[j][j]=alpha[j][j]*(1.0+(*alamda));
     oneda[j][0]=beta[j];
   }
 }
 dgaussj(covar,mfit,oneda,1);	/* matrix solution */
 for (j=0;j<mfit;j++) da[j]=oneda[j][0];
 if (*alamda == 0.0) {	/* once converged, evaluate covariance matrix */
   dcovsrt(covar,ma,ia,mfit);
   free_dmatrix(oneda);
   free_dvector(da);
   free_dvector(beta);
   free_dvector(atry);
   return;
 }
 for (j=-1,l=0;l<ma;l++)		/* did the trial succeed? */
 	if (ia[l]) atry[l]=a[l]+da[++j];
 dmrqcofD(x,y,sig,ndim,ndata,atry,ia,ma,covar,da,chisq,funcs);
 /*printf("chisq=%e\n",*chisq);*/
 if (*chisq < ochisq) {	/* Success, accept the new solution */
   *alamda *= 0.1;
   ochisq=(*chisq);
   for (j=-1,l=0;l<ma;l++) {
     if (ia[l]) {
       for (j++,k=-1,m=0;m<ma;m++) {
	  if (ia[m]) {
	    k++;
	    alpha[j][k] = covar[j][k];
	  }
	}
	beta[j]=da[j];
	a[l]=atry[l];
     }
   }
 } else {		/* failure, increase alamda and return */
   *alamda *= 10.0;
   *chisq=ochisq;
 }
}
