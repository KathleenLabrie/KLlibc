/* Function : stddev2D */
/* Version : 2.0.1 */
/* Average and stddev/variance. Mask rejection optional */
/* 2-D version */
/*
 * Return 0 if ok
 *
 * Needs:
 *   %%%libKLutil%%%
 */

#include <KLutil.h>
#include <stdio.h>  /* for gcc4.0, printf */
#include <math.h>
#include <stddef.h>	/* for NULL */

int stddev2D(double **data, unsigned long ii, unsigned long jj, 
	     unsigned long naxes[], unsigned long halfbox[], STATS *stats,
	     double **pmask)
{
 void nrerror(char error_text[]);
 long kk,ll;

 stats->stats_n=0;
 stats->stats_sum=0.0;
 stats->stats_sumsq=0.0;
 if ( pmask != NULL ) {
   for (ll=(long)(jj-halfbox[1]); ll<=(long)(jj+halfbox[1]); ll++) {
     for (kk=(long)(ii-halfbox[0]); kk<=(long)(ii+halfbox[0]); kk++) {
       if ((kk>=0) && (kk<naxes[0]) && (ll>=0) && (ll<naxes[1]) 
       	&& (*(*(pmask+ll)+kk) == 0) ) {
         stats->stats_sum += *(*(data+ll)+kk);
	  stats->stats_sumsq += SQR(*(*(data+ll)+kk));
	  (stats->stats_n)++;
       }
     }
   }
 }
 else {
   for (ll=(long)(jj-halfbox[1]); ll<=(long)(jj+halfbox[1]); ll++) {
     for (kk=(long)(ii-halfbox[0]); kk<=(long)(ii+halfbox[0]); kk++) {
       if ((kk>=0) && (kk<naxes[0]) && (ll>=0) && (ll<naxes[1])) {
         stats->stats_sum += *(*(data+ll)+kk);
	  stats->stats_sumsq += SQR(*(*(data+ll)+kk));
	  (stats->stats_n)++;
       }
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
