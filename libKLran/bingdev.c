/* Function : bingdev */
/* Version : 0.1.0 */
/*   Given a binned distribution ressembling a gaussian, returns
 *   a random deviate simulating that distribution.  Call with idum
 *   a negative to initialize; thereafter, do not alter idum between
 *   successive deviates in a sequence.
 *
 *   Uses the rejection method described in NR section 7.3.
 */

#include "./KLran.h"
#include <math.h>

#define SQRT2PI (sqrt(2*3.1415926535))

float bingdev(float *xbin, float *ybin, unsigned int nbin, long *idnum)
{
 int i;
 int bin,peak,wing;
 float firstdev,seconddev,fx,x;
 float stddev,F;
 int findbin(float x, float *xbin, unsigned int nbin);
 int findpeak(float *ybin, unsigned int nbin);

 /* set the gaussian parameters so that f(x) is larger than ybin */
 peak=findpeak(ybin,nbin);
 wing = ( (peak < nbin/2) ? nbin-1: 0 );
 stddev = sqrt( 0.5*pow((xbin[wing]-xbin[peak]),2)/log(ybin[peak]/ybin[wing]) );
 F = 1.25*ybin[peak]*stddev*SQRT2PI;

 do {
   /* First deviate - Gaussian */
   firstdev = gasdev(idnum);
   x = firstdev *stddev + xbin[peak];
   fx = 1./(stddev*SQRT2PI) * exp( -0.5*pow(firstdev,2) );
   fx *= F;

   /* Second deviate between 0 and fx - reject if not under ybin */
   if ( (bin = findbin(x,xbin,nbin)) > 0 ) {	/*within range; proceed*/
     seconddev = fx * ran1(idnum);
   }
 } while ((seconddev > ybin[bin]) || (bin<0));

 return x; 
}

int findbin(float x, float *xbin, unsigned int nbin)
{
 int bin;
 float inter;

 inter = xbin[1]-xbin[0];
 if (x < xbin[0]-inter/2.) return -1;	/* outside low bound */
 if (x >= xbin[nbin-1]+inter/2.) return -2;  /* outside high bound */
 bin = (int)( (x - (xbin[0]-inter/2.))/ inter );
 return bin;
}

int findpeak(float *ybin, unsigned int nbin)
{
 int bin,maxbin=0;

 for (bin=0;bin<nbin;bin++) { 
   if ( *(ybin+bin) > *(ybin+maxbin) ) { maxbin = bin; }
 }

 return maxbin;
}
