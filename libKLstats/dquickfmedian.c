/* Function : dquickfmedian */
/* Version: 1.0.0 */
/*	Calculates the median.  Accepts vector of doubles, returns double median.
 *  Uses 'dselect'.  The vector will be ALTERED.  Use 'fmedian' if that
 *  is a problem.
 *
 * double dquickfmedian( double vec[], unsigned long lenvec )
 *
 * Argument :
 *	Input : Vector of double values	- double vec[]
 *	  **** Will be altered ****
 *
 * Output :
 *	Median (double)
 *
 * Needs
 *   %%%libKLsort%%%
 */

#include <KLsort.h>		/* for dselect */

double dselect(unsigned long k, unsigned long n, double arr[]);

double dquickfmedian( double d_vec[], unsigned long lenvec )
{
 unsigned long middle;		
 /* middle is the middle element of a n elements vector (vec[0..n-1]) */
 double median;
 int i;

 middle = (lenvec % 2) ? (int)(lenvec/2)+1 : (int)(lenvec/2);
 if ( lenvec % 2 ) {
   median = dselect(middle, lenvec, d_vec);
 }
 else {
   median = (dselect(middle,lenvec,d_vec) + dselect(middle+1,lenvec,d_vec)) / 2.;
 }

 return(median);
}
