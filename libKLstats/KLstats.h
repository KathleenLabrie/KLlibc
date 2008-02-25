/* KLstats.h */

#ifndef _KL_STATS_H_
#define _KL_STATS_H_

#include <mystruct.h>

int dchisqimg(double **ppix1, double **ppix2, unsigned long int naxes[],
	unsigned long int section[],double **pstddev, double *chisq, 
	double *prob);
double dquickfmedian( double d_vec[], unsigned long lenvec );
void median2D( double **data, unsigned long ii, unsigned long jj,
	unsigned long naxes[], unsigned long halfbox[], double *median,
	double **pmask);
int medianbox( double **data, unsigned long naxes[], double *median,
	double **pmask);
void stddev(float *datavec, int n, float *ave, float *sdev, float *var);
int stddev2D(double **data, unsigned long ii, unsigned long jj, 
	     unsigned long naxes[], unsigned long halfbox[], STATS *stats,
	     double **pmask);
void stddevF2D(double **data, long ii, long jj, 
               unsigned long naxes[], unsigned long halfbox[], STATS *stats,
		 RASTER *rscan);
void stddevR2D(double **data, long ii, long jj, 
               unsigned long naxes[], unsigned long halfbox[], STATS *stats,
		 RASTER *rscan, double **pmask);
int stddevbox(double **data, unsigned long naxes[], STATS *stats, 
		double **pmask);

/* NR Functions */
void dchstwo(double bins1[], double bins2[], int nbins, int knstrn,
	double *df, double *chsq, double *prob);

#endif		 /* _KL_STATS_H_ */
