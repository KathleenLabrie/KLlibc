/* Function : dlfitg */
/* Version: 1.0.0 */
/* Least Square Fit using simple gauss elimination - no pivoting or scaling
 * strategies all matrices are sym-pos-def. 
 *
 * A . a = b
 *
 * Needs:
 *   %%%libKLutil%%%
 *   %%%libKLlinear%%%
 *
 */
/* WARNING: - sig[] is not actually being used yet 
 *	     - ia[] is not actually being used yet
 */

#include <myutil.h>
#include <KLlinear.h>
#include <math.h>

void dlfitg(double *x, double *y, double *sig, int ndat, double *a, 
	      int *ia, int ma, double *chisq, 
	      void (*funcs)(double, double [], int))
{
 int i,j,k;
 double **A, *b, *afunc;
 double sum;

 for (i=0; i<ndat; i++) sig[i]=1;
 for (k=0; k<ma; k++) ia[k]=1;

 A = dmatrixc(ma,ma);
 b = dvectorc(ma);
 afunc = dvector(ma);

 /* Build the least-square matrix, A[0..ma-1][0..ma-1] (A[k][j]) */
 for (k=0; k<ma; k++) {
   for (j=k; j<ma; j++) {
     for (i=0; i<ndat; i++) {
       if (*(x+i) != 0.0)
         *(*(A + k) + j) += pow(*(x+i), (double) (k)) * pow(*(x+i), (double) (j));
	else if ((ma <= 2) && (k+j == 0))
	  *(*(A + k) + j) += 1.0;
     }
     if (k != j)
     *(*(A + j) + k) = *(*(A + k) + j);
   }
 }

 /* Build up b[0..ma-1] */
 for (k=0; k<ma; k++) {
   for (i=0; i<ndat; i++) {
     if (*(x+i) != 0.0)
       *(b+k) += pow(*(x+i), (double) (k)) * (*(y+i));
     else if ((ma <= 2) && (k==0))
       *(b+k) += *(y+i);
   }
 }
 
 /* Proceed with gauss elimimation */
 dgauss(ma, A, b);

 /* Solution */
 for (k=0; k<ma; k++) {
   a[k] = b[k];
 }

 /* Chi^2 */
 *chisq=0;
 for (i=0; i<ndat; i++) {
   (*funcs)(x[i], afunc, ma);
   for (sum=0.0, j=0; j<ma; j++) sum += a[j]*afunc[j];
   *chisq += DSQR((y[i]-sum)/sig[i]);
 }

 free_dvector(b);
 free_dmatrix(A);
 free_dvector(afunc);
 return;
}
