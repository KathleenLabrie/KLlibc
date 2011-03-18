/* Header: KLimgutil.h */
/* Version: 0.1.0 */
/* Library: libKLimgutil.a */
/*	Library of image manipulation routines */

#ifndef _KL_IMGUTIL_H_
#define _KL_IMGUTIL_H_

#include <KLutil.h>

/* Error codes */
#define FILE_NOT_OPENED 104
#define WRITE_ERROR 106
#define FILE_NOT_CLOSED 110
#define ARRAY_TOO_BIG 111

#define BAD_PIXEL 1
#define HOT_PIXEL 2

#define MAXNBPT 40000

void clip(int iter, double **ppix, long ii, long jj, STATS *stats, CLIP *cpar,
		double **pdeviant);
int make_mask(double **pcoo, unsigned long npts, long naxes[], 
                double ***ptr2mask);
int read_points( char filename[], double ***ptr2pcoo, unsigned long *npts,
                 long dx, long dy );
int shift_image( double **ppix, long naxes[], long dii, long djj );
void stddev4clip(int iter,CLIP *cpar, double **ppix, double **pmask, long ii, 
	long jj, long naxes[], unsigned long halfsigbox[2], 
	STATS *stats, RASTER *rscan, double **pdeviant);
int wrlog( char logfile[], char message[] );

#endif 	/* _KL_IMGUTIL_H */
