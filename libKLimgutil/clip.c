/* Function: clip */
/* Version: 0.1.0 */
/*	Statistical clipping of pixels 
 *
 *Needs:
 *   %%%libKLutil%%%
 */

#include "./KLimgutil.h"
#include <KLutil.h>

void clip(int iter, double **ppix, long ii, long jj, STATS *stats, CLIP *cpar,
		double **pdeviant)
{
 if ( *(*(ppix+jj) + ii) < (stats->stats_ave - 
		      		cpar->clip_lsigma[iter]*stats->stats_sdev) ) {
   *(*(pdeviant+jj)+ii) = BAD_PIXEL;
 }
 else if ( *(*(ppix+jj)+ii) > (stats->stats_ave +
		      		cpar->clip_hsigma[iter]*stats->stats_sdev) ) {
   *(*(pdeviant+jj)+ii) = HOT_PIXEL;
 }
 return;
}
