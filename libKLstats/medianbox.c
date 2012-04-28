/* Function: medianbox */
/* Version: 1.0.1
 * 	Calculate median of a box of data.  Can use mask.
 *
 * int medianbox( double **data, long naxes[], > double *median,
 *	double **pmask)
 *
 * Arguments:
 *	Inputs:
 *		Data points		- double **data
 *		Size of matrix	- unsigned long naxes[]
 *		Mask			- double **pmask
 *
 *	Output:
 *		Median			- double *median
 *
 * Output:
 *	Error code: 0 if no error; 1+ if error;
 *
 * Calling medianbox
 *	status = medianbox( data, naxes, &median, pmask );
 *	status = medianbox( data, naxes, &median, NULL );
 *
 * Needs:
 *   %%%libKLutil%%%
 */

#include "./KLstats.h"
#include <myutil.h>
#include <stddef.h>	/* for NULL */

int medianbox( double **data, long naxes[], double *median,
	double **pmask)
{
 unsigned long kk,ll,len,i=0;
 double *vec;
 
 len = naxes[1] * naxes[0];
 vec = dvector(len);

 /* get vector */
 if ( pmask != NULL ) {
   for (ll=0; ll<naxes[1]; ll++) {
     for (kk=0; kk<naxes[0]; kk++) {
       if (*(*(pmask+ll)+kk) == 0) {
		*(vec+i) = *(*(data+ll)+kk);
		i++;
	}
     }
   }
 }
 else {
   for (ll=0; ll<naxes[1]; ll++) {
     for (kk=0; kk<naxes[0]; kk++) {
     		*(vec+i) = *(*(data+ll)+kk);
		i++;
     }
   }
 }
 
 len = i;
 *median = dquickfmedian(vec, len);
 free_dvector(vec);
 
 return(0);
}
