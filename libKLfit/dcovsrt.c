/* Function : dcovsrt */
/* From NR function : covsrt
 *   Expand in storage the covariance matrix covar, so as to take into
 *   account parameters that are being held fixed.  (For the later,
 *   return zero covariances.
 *
 * void dcovsrt(double **covar, int ma, int ia[], int mfit);
 *	Inputs:
 *		**covar	- ma x ma matrix
 *		ma		- number of parameters
 *		ia[ma]		- id parameters to be fit
 *		mfit		- number of parameters to fit.
 *	Output:
 *		**covar	- ma x ma matrix
 *
 * Calling dcovsrt:
 *	dcovsrt(covar, ma, ia, mfit);
 *
 * Needs:
 * */

#define SWAP(a,b) {swap=(a);(a)=(b);(b)=swap;}

void dcovsrt(double **covar, int ma, int ia[], int mfit)
{
 int i,j,k;
 double swap;

 for (i=mfit;i<ma;i++)
 	for (j=0;j<=i;j++) covar[i][j]=covar[j][i]=0.0;
 k=mfit-1;
 for (j=ma-1;j>=0;j--) {
   if (ia[j]) {
     for (i=0;i<ma;i++) SWAP(covar[i][k],covar[i][j])
     for (i=0;i<ma;i++) SWAP(covar[k][i],covar[j][i])
     k--;
   }
 }
}
