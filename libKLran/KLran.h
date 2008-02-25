/* KLran.h */

#ifndef _KL_RAN_H_
#define _KL_RAN_H_

float gamdev(int ia, long int *idum);
float gasdev(long int *idum);
float poidev(float xm, long int *idum);
float ran1(long int *idum);
float ran2(long int *idum);
void ran2D( long int *seed, float *x, float *y );

float bingdev(float *xbin, float *ybin, unsigned int nbin, long *idnum);

#endif		/* _KL_RAN_H_ */
