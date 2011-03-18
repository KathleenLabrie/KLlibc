/* Function : gconv2d */
/* Version : 0.1.0 */
/*   Wrapper to conv2d.  Convolve image with Gaussian function.
 *   WARNING: 'theta' not implemented.
 *
 * int gconv2d(double **ppix, long int naxes[], double sigma, double ratio,
 *		double theta, double width);
 *
 *	ratio:	y to x
 *
 * Calling gconv2d
 *   status = gconv2d(&ppix,naxes,sigma,ratio,theta,width);
 *
 * Needs:
 *   %%%libKLfunc%%%
 *   %%%libKLutil%%%
 */

#include "./KLfft.h"
#include <KLutil.h>
#include <KLfunc.h>	/* for gauss */
#include <stdio.h>	/* for stderr */
#include <stddef.h>	/* for NULL */

static void pre_return(void);

/* File Scope variables */
static double **presp=NULL;
static double **points=NULL,*values=NULL,*coeff=NULL;

int gconv2d(double **ppix, long int naxes[], double sigma, double ratio,
	double theta, double width)
{
 int status=0;
 long int ii,jj,j;
 long int img_naxes[2], gauss_naxes[2], npoints=0;
 double norm;
 void (*pfunc)();
 
 /*********/
 theta=0.;
 /*********/

 img_naxes[0]=naxes[0];
 img_naxes[1]=naxes[1];
 gauss_naxes[0]=gauss_naxes[1]=(long int)(width*sigma);
 if (gauss_naxes[0]%2 == 0) { gauss_naxes[0]++; } /* naxes must be odd */
 if (gauss_naxes[1]%2 == 0) { gauss_naxes[1]++; }

 /* Get response function, i.e. Gaussian */
 presp = dmatrixc(gauss_naxes[1],gauss_naxes[0]);
 npoints = gauss_naxes[1]*gauss_naxes[0];
 points = dmatrix(2,npoints);
 values = dvectorc(npoints);
 for (j=0,jj=0;jj<gauss_naxes[1];jj++)
   for (ii=0;ii<gauss_naxes[1];ii++) {
     *(*(points+0)+j) = (double)ii;
     *(*(points+1)+j) = (double)jj;
     j++;
   }
 pfunc = fgaussS;
 coeff = dvector(NCOEFF_GAUSS_SURFACE);
 coeff[0]=0.;
 coeff[1]=1.;
 coeff[2]=gauss_naxes[0]/2;
 coeff[3]=gauss_naxes[1]/2;
 coeff[4]=sigma;
 coeff[5]=sigma*ratio;
 if (status = evalfunc(points,values,2,npoints,coeff,NCOEFF_GAUSS_SURFACE,pfunc)) {
	fprintf(stderr,ERRMSG_INTERNAL_ERROR);
	pre_return();
	return(ERRNO_INTERNAL_ERROR);
 }
 for (norm=0,j=0;j<npoints;j++) norm += *(values+j);
 for (j=0;j<npoints;j++)
   *(*(presp+(long int)points[1][j])+(long int)points[0][j]) = *(values+j)/norm;
 
 /* Free some memory */
 free_dmatrix(points);
 free_dvector(values);
 free_dvector(coeff);
 points=NULL;
 values=coeff=NULL;
 
 if ( status = conv2d(ppix,presp,img_naxes,gauss_naxes) ) {
 	fprintf(stderr,ERRMSG_INTERNAL_ERROR);
	pre_return();
	return(ERRNO_INTERNAL_ERROR);
 }

 pre_return();
 return(status);
}

void pre_return(void)
{
 if (presp != NULL)	{ free_dmatrix(presp); }
 if (points != NULL)	{ free_dmatrix(points); }
 if (values != NULL)    { free_dvector(values); }
 if (coeff != NULL)     { free_dvector(coeff); }
 
 return;
}
