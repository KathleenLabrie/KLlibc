/* Function : dclean */
/* Version : 0.1.0 */
/*   Eliminate duplicate numbers in a sorted vector a[0..n-1].  returns the
 *   effective length of the 'cleaned' vector; a is replaces by the 
 *   'cleaned' vector.
 *
 *   **** Remember to sort the vector first ****
 *
 * Needs:
 *   %%%libKLutil%%%
 */

#include <KLutil.h>	/* for dvector() and equals() */

unsigned long dclean(unsigned long n, double a[])
{
 unsigned long i,j;
 double *v;

 v=dvector(n); 
 v[0]=a[0];
 for (j=0,i=1;i<n;i++) {
   /* if (a[i] != v[j]) { v[++j] = a[i]; } */
   if ( !equals(a[i],v[j]) ) { v[++j] = a[i]; }
   a[i]=0;
 }
 n=j+1;
 for (j=0;j<n;j++) { a[j] = v[j]; }

 return(n);
}
