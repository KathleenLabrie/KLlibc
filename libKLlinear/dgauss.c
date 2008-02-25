/* Function : dgauss */
/* Simple gauss elimination - no pivoting or scaling strategies
 * all matrices are sum-pos-def
 * Taken from Xmgr, modified.
 *
 * A.x = b
 *
 * x is return through b
 *
 * void dgauss(int n, double **a, double *b);
 *	Inputs:
 *		n	- size of input matrix A
 *		a	- input n x n matrix A
 *		b	- input right-hand side vector
 *	Output:
 *		b	- solution vector x
 *
 * Calling dgauss:
 *	dgauss(n, a, b);
 *
 * Needs:
 */

void dgauss(int n, double **a, double *b)
{
 int i,k,j;
 double mult;

 for (k=0;k<n-1;k++) {
   for (i=k+1;i<n;i++) {
     mult = *(*(a+i)+k) / *(*(a+k)+k);
     for (j=k+1; j<n; j++) 
       *(*(a+i)+j) -= mult * (*(*(a+k)+j));
     *(b+i) -= mult * (*(b+k));
   }
 }
 for (i=n-1; i>=0; i--) {
   for (j=i+1; j<n; j++) 
     *(b+i) -= *(*(a+i)+j) * (*(b+j));
   *(b+i) /= *(*(a+i)+i);
 }
}
