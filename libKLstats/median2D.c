/* Function: median2D */
/* Version: 1.0.1 */
/*
 * Calculate median of a box from a 2D image matrix.  Can use mask.
 *
 * void median2D( double **data, unsigned long ii, unsigned long jj,
 *	long naxes[], unsigned long halfbox[], > double *median,
 *	double **pmask)
 *
 * Needs:
 *   %%%libKLutil%%%
 */

#include "./KLstats.h"		/* for dquickfmedian */
#include <myutil.h>
#include <stddef.h>		/* for NULL */

void median2D( double **data, unsigned long ii, unsigned long jj,
	long naxes[], unsigned long halfbox[], double *median,
	double **pmask)
{
 long int kk,ll,len,i=0;
 double *vec;
 
 len = ( 2*halfbox[0] + 1 ) * ( 2*halfbox[1] + 1 );
 vec = dvector(len);

 /* get vector */
 if ( pmask != NULL ) {
   for (ll=(long)(jj-halfbox[1]); ll<=(long)(jj+halfbox[1]); ll++) {
     for (kk=(long)(ii-halfbox[0]); kk<=(long)(ii+halfbox[0]); kk++) {
       if ((kk>=0) && (kk<naxes[0]) && (ll>=0) && (ll<naxes[1])
       	&& (*(*(pmask+ll)+kk) == 0) ) {
	  *(vec+i) = *(*(data+ll)+kk);
	  i++;
	}
     }
   }
 }
 else {
   for (ll=(long)(jj-halfbox[1]); ll<=(long)(jj+halfbox[1]); ll++) {
     for (kk=(long)(ii-halfbox[0]); kk<=(long)(ii+halfbox[0]); kk++) {
       if ((kk>=0) && (kk<naxes[0]) && (ll>=0) && (ll<naxes[1])) {
	  *(vec+i) = *(*(data+ll)+kk);
	  i++;
	}
     }
   }
 }
 
 len = i;
 *median = dquickfmedian(vec, len);
 free_dvector(vec);
 
 return;
}
