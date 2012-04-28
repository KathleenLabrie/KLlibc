/* Function : dgaussj */
/* NR function : gaussj 
 *   Gauss-Jordan elimination with full pivoting.
 *
 *   Can solve multiple linear sets together.  
 *   A.x1=b1 , A.x2=b2, A.xm=bm.
 *
 * void dgaussj(double **a, int n, double **b, int m);
 *	Inputs:
 *		a	- input n x n matrix
 *		n	- size of matrix a
 *		b	- n x m input containing the m right-hand side vectors
 *		m	- number of right-hand side vectors.
 *	Outputs:
 *		b	- corresponding set of solution vectors x.
 *
 * Calling dgaussj:
 *	dgaussj(a, n, b, m);
 *
 * Needs:
 *   %%%KLutil%%%
 */


#include <math.h>
#include <KLutil.h>
#include <stdio.h>
#include <stdlib.h>
#define SWAP(a,b) {temp=(a);(a)=(b);(b)=temp;}

void dgaussj(double **a, int n, double **b, int m)
{
 int *indxc,*indxr,*ipiv=NULL;
 int i,icol,irow,j,k,l,ll;
 double big,dum,pivinv,temp;

 indxc=ivector(n);
 indxr=ivector(n);
 ipiv=ivector(n);

 for (j=0;j<n;j++) ipiv[j]=0;
 for (i=0;i<n;i++) {
   big=0.0;
   for (j=0;j<n;j++)
   	if (ipiv[j] != 1)
		for (k=0;k<n;k++) {
		  if (ipiv[k] == 0) {
		    if (fabs(a[j][k]) >= big) {
		      big=fabs(a[j][k]);
		      irow=j;
		      icol=k;
		    }
		  } else if (ipiv[k] > 1) rterror("gaussj: Singular Matrix-1");
		}
   ++(ipiv[icol]);
   if (irow != icol) {
     for (l=0;l<n;l++) SWAP(a[irow][l],a[icol][l])
     for (l=0;l<m;l++) SWAP(b[irow][l],b[icol][l])
   }
   indxr[i]=irow;
   indxc[i]=icol;
   if (a[icol][icol] == 0) rterror("gaussj: Singular Matrix-2");
   pivinv=1.0/a[icol][icol];
   a[icol][icol]=1.0;
   for (l=0;l<n;l++) a[icol][l] *= pivinv;
   for (l=0;l<m;l++) {
     b[icol][l] *= pivinv;
   }
   for (ll=0;ll<n;ll++)
   	if (ll != icol) {
	  dum=a[ll][icol];
	  a[ll][icol]=0.0;
	  for (l=0;l<n;l++) a[ll][l] -= a[icol][l]*dum;
	  for (l=0;l<m;l++) b[ll][l] -= b[icol][l]*dum;
	}
 }
 for (l=n-1;l>=0;l--) {
   if (indxr[l] != indxc[l])
   	for (k=0;k<n;k++)
		SWAP(a[k][indxr[l]],a[k][indxc[l]]);
 }
 free_ivector(ipiv);
 free_ivector(indxr);
 free_ivector(indxc);
}
