/* Function : dchisqimg */
/* Version : 0.1.0 */
/*  Calculate chisq of flux in each pixel of a true image, ppix1,
 *  versus a fake image, ppix2.  prob equals Q=1-P(a,x).
 *
 * int dchisqimg(double **ppix1, double **ppix2, long int naxes[],
 *	double *chisq, double *prob);
 *
 * Calling dchisqimg
 *   status = dchisqimg(ppix1,ppix2,naxes,&chisq,&prob);
 *
 * Needs:
 *   %%%libKLfunc%%%
 */

#include <KLfunc.h>	/* for gammq() */
#include <stdio.h>

int dchisqimg(double **ppix1, double **ppix2, long int naxes[],
	unsigned long int section[], double **pstddev, double *chisq,
	double *prob)
{
 int status=0;
 unsigned long int ii,jj;
 double temp,sigma;
 float df;
 
 /* df = naxes[0]*naxes[1] - 1.; */
 df = (section[3]-section[2]+1)*(section[1]-section[0]+1)-1;
 *chisq=0.0;
 for (jj=section[2]-1;jj<section[3];jj++) {
   for (ii=section[0]-1;ii<section[1];ii++) {
     temp = *(*(ppix1+jj)+ii) - *(*(ppix2+jj)+ii);
     sigma = *(*(pstddev+jj)+ii);
     if (sigma == 0.) { df--; }
     else { *chisq += temp*temp/(sigma*sigma); }
   }
   /* if ((jj == 233)) printf("%d,%d temp=%g  sigma=%g\n",ii,jj,temp,sigma); */
 }
 /* printf("df=%g  chisq=%g   ",df,*chisq);
 fflush(stdout); */
 *prob=(double)gammq(0.5*df,(float)0.5*(*chisq));
 /* printf("prob=%g\n",*prob);
 fflush(stdout); */

 return(status);
}
