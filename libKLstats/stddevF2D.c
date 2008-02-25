/* Function: stddevF2D */
/* Version: 2.0.1 */
/* Uses sum and sum of squares to calculate variance.  Raster scan.
 * Does not handle distributions around zero (i.e. with + and - values)
 *
 * Needs:
 *   %%%libKLutil%%%
 */

#include <KLutil.h>
#include <math.h>
#include <stdio.h>

void stddevF2D(double **data, long ii, long jj, 
               unsigned long naxes[], unsigned long halfbox[], STATS *stats,
		 RASTER *rscan)
{
 void rterror(char error_text[]);
 long kk,ll;
 double s,p;


 /* First pixel */
 if (rscan->rstr_up == -1) {
   stats->stats_n=0;
   stats->stats_sum=0.0;
   stats->stats_sumsq=0.0;
   for (ll=(long)(jj-halfbox[1]); ll<=(long)(jj+halfbox[1]); ll++) {
     for (kk=(long)(ii-halfbox[0]); kk<=(long)(ii+halfbox[0]); kk++) {
	if ((kk>=0) && (kk<naxes[0]) && (ll>=0) && (ll<naxes[1])) {
         stats->stats_sum += *(*(data+ll)+kk);
	  stats->stats_sumsq += SQR(*(*(data+ll)+kk));
	  (stats->stats_n)++;
	}
     }
   }
   if (stats->stats_n <= 1) {rterror("n must be at least 2 in stddev");}

   rscan->rstr_oldcol = -1;
   rscan->rstr_newcol = halfbox[0]+1;
   rscan->rstr_oldline = -1;
   rscan->rstr_newline = halfbox[1]+1;
   rscan->rstr_up = 0;
 }

 /* Going up */
 else if (rscan->rstr_up) {

   /* Delete points in previous 'sum' and 'sumsq', adjust 'n' */
   if ((rscan->rstr_oldline >= 0) && (rscan->rstr_oldline < naxes[1])) {
     for (kk=(long)(ii-halfbox[0]); kk<=(long)(ii+halfbox[0]); kk++) {
       if ((kk>=0) && (kk<naxes[0])) {
	  stats->stats_sum -= *(*(data+rscan->rstr_oldline)+kk);
	  stats->stats_sumsq -= SQR( *(*(data+rscan->rstr_oldline)+kk) );
	  (stats->stats_n)--;
	}
     }
   }

   /* Add the new points to 'sum' and 'sumsq', adjust 'n' */
   if ((rscan->rstr_newline >= 0) && (rscan->rstr_newline < naxes[1])) {
     for (kk=(long)(ii-halfbox[0]); kk<=(long)(ii+halfbox[0]); kk++) {
       if ((kk>=0) && (kk<naxes[0])) {
	  stats->stats_sum += *(*(data+rscan->rstr_newline)+kk);
	  stats->stats_sumsq += SQR( *(*(data+rscan->rstr_newline)+kk) );
	  (stats->stats_n)++;
	}
     }
   }

   /* Fix rscan */
   rscan->rstr_up=0;
   rscan->rstr_newline++;
   rscan->rstr_oldline = rscan->rstr_newline - 2*halfbox[1] - 1;
   if (jj % 2) {		/* Going left */
     rscan->rstr_newcol = (naxes[0]-1) - halfbox[0] - 1;
     rscan->rstr_oldcol = rscan->rstr_newcol + 2*halfbox[0] + 1;
   }
   else {			/* Going right */
     rscan->rstr_newcol = halfbox[0]+1;
     rscan->rstr_oldcol = rscan->rstr_newcol - 2*halfbox[0] - 1;
   }
 }
 /* Right or left */
 else {

   /* Delete points in previous 'sum' and 'sumsq', adjust 'n' */
   if ((rscan->rstr_oldcol >=0) && (rscan->rstr_oldcol < naxes[0])) {
     for (ll=(long)(jj-halfbox[1]); ll<=(long)(jj+halfbox[1]); ll++) {
       if ((ll>=0) && (ll<naxes[1])) {
	  stats->stats_sum -= *(*(data+ll)+rscan->rstr_oldcol);
	  stats->stats_sumsq -= SQR( *(*(data+ll)+rscan->rstr_oldcol) );
	  (stats->stats_n)--;
	}
     }
   }
   
   /* Add the new points to 'sum' and 'sumsq', adjust 'n' */
   if ((rscan->rstr_newcol >= 0) && (rscan->rstr_newcol < naxes[0])) {
     for (ll=(long)(jj-halfbox[1]); ll<=(long)(jj+halfbox[1]); ll++) {
       if ((ll>=0) && (ll<naxes[1])) {
	  stats->stats_sum += *(*(data+ll)+rscan->rstr_newcol);
	  stats->stats_sumsq += SQR( *(*(data+ll)+rscan->rstr_newcol) );
	  (stats->stats_n)++;
	}
     }
   }
   

   /* Fix rscan */
   if (rscan->rstr_oldcol < rscan->rstr_newcol) {	/* Going right */
     rscan->rstr_newcol++;
	 rscan->rstr_oldcol = rscan->rstr_newcol - 2*halfbox[0] - 1;
   }
   else {						/* Going left */
     rscan->rstr_newcol--;
	 rscan->rstr_oldcol = rscan->rstr_newcol + 2*halfbox[0] + 1;
   }
 }

 
 /* Calculate stats */
 stats->stats_ave = stats->stats_sum / stats->stats_n;
 stats->stats_var = (stats->stats_sumsq -
 			(1./(double)(stats->stats_n))*SQR(stats->stats_sum)) / 
		      (double)(stats->stats_n - 1);
 stats->stats_sdev = sqrt(abs(stats->stats_var));

 return;
}
