/* Function : conv2d */
/*   Convolve an image with a response function 
 *   Call from one of the wrappers [gconv2d, mconv2d]
 *
 */

#include "./KLfft.h"
#include <KLutil.h>
#include <stddef.h>	/* for NULL */
#include <math.h>
#include <stdio.h>

int conv2d(double **ppix, double **presp, long int img_naxes[],
	long int resp_naxes[])
{
 int status=0;
 long int ii,jj,kk,ll,j;
 long int fft_naxes[2];
 double ***datap=NULL,***datar=NULL,**speqp=NULL,**speqr=NULL;
 double fac,*sp1,*sp2,r,i;

 fft_naxes[0]=fft_naxes[1]=
 	pow(2.,ceil(log10(img_naxes[0]+(resp_naxes[0]/2.))/log10(2.)));

 /* Copy image and response function to dcubes, and add zero-padding
  * Arrange response function in wrap-around format */
 datap = dcubec(1,fft_naxes[1],fft_naxes[0]);
 datar = dcubec(1,fft_naxes[1],fft_naxes[0]);
 speqp = dmatrix(1,2*fft_naxes[1]);
 speqr = dmatrix(1,2*fft_naxes[1]);
 
 for (jj=0;jj<img_naxes[1];jj++)	/* image */
   for (ii=0;ii<img_naxes[0];ii++)
     *(*(*(datap+0)+jj)+ii) = *(*(ppix+jj)+ii);

 for (jj=0,ll=-(int)(resp_naxes[1]/2);jj<resp_naxes[1];jj++,ll++) /* response*/
   for (ii=0,kk=-(int)(resp_naxes[0]/2);ii<resp_naxes[0];ii++,kk++) {
     if ((ll<0) && (kk<0))
     	*(*(*(datar+0)+fft_naxes[1]+ll)+fft_naxes[0]+kk) = *(*(presp+jj)+ii);
     else if (ll<0)
     *(*(*(datar+0)+fft_naxes[1]+ll)+kk) = *(*(presp+jj)+ii);
     else if (kk<0)
        *(*(*(datar+0)+ll)+fft_naxes[0]+kk) = *(*(presp+jj)+ii);
     else
        *(*(*(datar+0)+ll)+kk) = *(*(presp+jj)+ii);

   }

 /* Calculate Fourier transforms of image and response */
 drlft3(datap,speqp,1,fft_naxes[1],fft_naxes[0],1);
 drlft3(datar,speqr,1,fft_naxes[1],fft_naxes[0],1);
  
 /* Convolve, i.e. multiply Fourier transforms */
 fac=2.0/(1.*fft_naxes[1]*fft_naxes[0]);
 sp1 = &datap[0][0][0];
 sp2 = &datar[0][0][0];
 for (j=0; j<1*fft_naxes[1]*fft_naxes[0]/2; j++) {
   r = sp1[0]*sp2[0] - sp1[1]*sp2[1];
   i = sp1[0]*sp2[1] + sp1[1]*sp2[0];
   sp1[0] = fac*r;
   sp1[1] = fac*i;
   sp1 += 2;
   sp2 += 2;
 }
 sp1 = &speqp[0][0];
 sp2 = &speqr[0][0];
 for (j=0; j<1*fft_naxes[1]; j++) {
   r = sp1[0]*sp2[0] - sp1[1]*sp2[1];
   i = sp1[0]*sp2[1] + sp1[1]*sp2[0];
   sp1[0] = fac*r;
   sp1[1] = fac*i;
   sp1 += 2;
   sp2 += 2;
 }
 
 /* Inverse Fourier transform of convolved image */
 drlft3(datap,speqp,1,fft_naxes[1],fft_naxes[0],-1);
 
 /* Copy convolved image to original array and remove zero-padding */
 for (jj=0;jj<img_naxes[1];jj++)
   for (ii=0;ii<img_naxes[0];ii++)
     *(*(ppix+jj)+ii) = *(*(*(datap+0)+jj)+ii);

 free_dcube(datap);
 free_dcube(datar);
 free_dmatrix(speqp);
 free_dmatrix(speqr);

 return(status);
}
