/* Function : mconv2d */
/* Version : 0.1.0 */
/*   Wrapper to conv2d.  Convolve image with Moffat function.
 *   WARNING: 'theta' not implemented.
 *   Note: beta is usually -2.5
 *
 * int mconv2d(double **ppix, long int naxes[], double sigma, double ratio,
 *		double theta, double beta, double width);
 *
 *	ratio:	y to x
 *
 * Calling mconv2d
 *   status = mconv2d(&ppix,naxes,sigma,ratio,theta,beta,width);
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

int mconv2d(double **ppix, long int naxes[], double sigma, double ratio,
	double theta, double beta, double width)
{
 int status=0;
 long int ii,jj,j;
 long int img_naxes[2], resp_naxes[2], npoints=0;
 double norm;
 void (*pfunc)();
 
 /*********/
 theta=0.;
 /*********/
 
 img_naxes[0]=naxes[0];
 img_naxes[1]=naxes[1];
 resp_naxes[0]=resp_naxes[1]=(long int)(width*sigma);
 if (resp_naxes[0]%2 == 0) { resp_naxes[0]++; } /* naxes must be odd */
 if (resp_naxes[1]%2 == 0) { resp_naxes[1]++; }

 /* Get response function, i.e. Moffatt */
 presp = dmatrixc(resp_naxes[1],resp_naxes[0]);
 npoints = resp_naxes[1]*resp_naxes[0];
 points = dmatrix(2,npoints);
 values = dvectorc(npoints);
 for (j=0,jj=0;jj<resp_naxes[1];jj++)
   for (ii=0;ii<resp_naxes[1];ii++) {
     *(*(points+0)+j) = (double)ii;
     *(*(points+1)+j) = (double)jj;
     j++;
   }
 pfunc = fmoffatS;
 coeff = dvector(NCOEFF_MOFFAT_SURFACE);
 coeff[0]=0.;
 coeff[1]=1.;
 coeff[2]=resp_naxes[0]/2;
 coeff[3]=resp_naxes[1]/2;
 coeff[4]=beta;
 coeff[5]=sigma;
 coeff[6]=sigma*ratio;
 if (status = evalfunc(points,values,2,npoints,coeff,NCOEFF_MOFFAT_SURFACE,pfunc)) {
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
 
 if ( status = conv2d(ppix,presp,img_naxes,resp_naxes) ) {
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
