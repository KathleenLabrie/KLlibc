/* Function: stddevbox.c */
/* Version: 1.0.2
 *	Sum, sum of squares, average, variance and stddev of a box of value.
 *	Mask is optional.
 *
 * int stddevbox( double **data, long naxes[], STATS *stats,
 *		    double **pmask );
 *
 * Arguments:
 * 	Inputs:
 *		Data points		- double **data
 *		Size of matrix	- unsigned long naxes[]
 *		Mask			- double **pmask
 *
 *	Output:
 *		Stats			- STATS *stats
 *
 * Output:
 *	Error code: 0 if no error; 1+ if error;
 *
 * Calling stddevbox
 *	status = stddevbox( data, naxes, &stats, pmask );
 *	status = stddevbox( data, naxes, &stats, NULL );
 *
 * Needs
 *   %%%libKLutil%%%
 */

#include <KLutil.h>
#include <stdio.h>      /* for gcc4.0, printf */
#include <math.h>
#include <stddef.h>		/* for NULL */

int stddevbox(double **data, long naxes[], STATS *stats, 
		double **pmask)
{
 void nrerror(char error_text[]);
 unsigned long kk,ll;

 stats->stats_n=0;
 stats->stats_sum=0.0;
 stats->stats_sumsq=0.0;
 if ( pmask != NULL ) {
   for (ll=0; ll<naxes[1]; ll++) {
     for (kk=0; kk<naxes[0]; kk++) {
       if ( *(*(pmask+ll)+kk) == 0 ) {
		stats->stats_sum += *(*(data+ll)+kk);
		stats->stats_sumsq += SQR(*(*(data+ll)+kk));
		(stats->stats_n)++;
       }
     }
   }
 }
 else {
   for (ll=0; ll<naxes[1]; ll++) {
     for (kk=0; kk<naxes[0]; kk++) {
         stats->stats_sum += *(*(data+ll)+kk);
	  stats->stats_sumsq += SQR(*(*(data+ll)+kk));
	  (stats->stats_n)++;
     }
   }
 }
 
 if (stats->stats_n <= 1) {
   printf("ERROR: n must be at least 2 in stddev\n");
   return(1);
 }

 /* Calculate stats */
 stats->stats_ave = stats->stats_sum / stats->stats_n;
 stats->stats_var = (stats->stats_sumsq -
                       (1./(double)(stats->stats_n))*SQR(stats->stats_sum)) /
		       (double)(stats->stats_n - 1);
 stats->stats_sdev = sqrt(abs(stats->stats_var));

 return(0);
}
