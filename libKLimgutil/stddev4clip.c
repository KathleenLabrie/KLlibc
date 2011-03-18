/* Function: stddev4clip */
/* Version: 0.1.0 */
/*	Calculate stddev as required for the clipping type.
 *
 * Needs:
 *   %%%KLutil%%%
 *   %%%KLstats%%%
 */

#include <KLutil.h>
#include <KLstats.h>
#include <stddef.h>	/* for NULL */

void stddev4clip(int iter,CLIP *cpar, double **ppix, double **pmask, long ii, 
	long jj, unsigned long naxes[], unsigned long halfsigbox[2], 
	STATS *stats, RASTER *rscan, double **pdeviant)
{
 /* define halfsigbox */
 halfsigbox[0]=(unsigned long)cpar->clip_sigbox[iter][0]/2;
 halfsigbox[1]=(unsigned long)cpar->clip_sigbox[iter][1]/2;

 switch (cpar->clip_tclip[iter]) {
   case CCDCLIP:
      /* need to compute average */
      stddevF2D(ppix,ii,jj,naxes,halfsigbox,stats,rscan);
      /* define sdev from CCD characteristics and local average */
      stats->stats_sdev = 
	 sqrt(DSQR(cpar->clip_chip.ccd_rnoise/cpar->clip_chip.ccd_gain) +
	      stats->stats_ave/cpar->clip_chip.ccd_gain +
	      DSQR(stats->stats_ave * cpar->clip_chip.ccd_snoise)
	     );
      break;
   case SIGCLIP:
      stddevF2D(ppix,ii,jj,naxes,halfsigbox,stats,rscan);
      break;
   case SIGCLIPR:	/*just in case I enter it, but still perform CLIPB*/
   case SIGCLIPB:
      if ((iter+1 == 1) && (pmask == NULL)) {
	 printf("ERROR: Cannot SIGCLIPB in iteration 1. Have nothing "
		 "to reject yet.\n");
      }
      stddevR2D(ppix,ii,jj,naxes,halfsigbox,stats,rscan,pdeviant);
      break;
   default:
      printf("ERROR: Invalid clipping type in iteration %d (tclip=%d)\n",
	      iter+1,cpar->clip_tclip[iter]);
      exit(1);
 }
 return;
}
