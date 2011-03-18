/* Main : testndim */
/* Version: 0.1.0 */
/*   Test multidimensional FFT routines
 *
 * Needs:
 *   %%%libKLutil%%%
 *   %%%libKLcfitsio%%%
 */

#include "./KLfft.h"
#include <KLutil.h>
#include <KLcfitsio.h>
#include <stdio.h>

#define N2 16	/* size of image */
#define N3 16	/* size of image */

main()
{
 int nheaders;
 long int j,ii,jj;
 long int naxes[2];
 double **ppix=NULL, **presp=NULL;
 double ***datap=NULL, ***datar=NULL, **speqp=NULL, **speqr=NULL;
 double fac, r, i, *sp1, *sp2;
 KLFITS_HEADER *headers=NULL;

 nheaders = 0;
 naxes[0]=N3;
 naxes[1]=N2;
 ppix = dmatrixc(N2,N3);
 *(*(ppix+(long int)N2/4)+(long int)N3/4) = 1.;
 
 presp = dmatrixc(N2,N3);
 *(*(presp+0)+0) = 1.;
 *(*(presp+0)+1) = 0.5;
 *(*(presp+0)+naxes[0]-1) = 0.5;
  *(*(presp+1)+0) = 0.5;
 *(*(presp+naxes[1]-1)+0) = 0.5;
 *(*(presp+1)+1) = 0.25;
 *(*(presp+1)+naxes[0]-1) = 0.25;
 *(*(presp+naxes[1]-1)+1) = 0.25;
 *(*(presp+naxes[1]-1)+naxes[0]-1) = 0.25;
 
 datap = dcube(1,N2,N3);
 datar = dcube(1,N2,N3);
 speqp = dmatrix(1,2*N2);
 speqr = dmatrix(1,2*N2);

 for (jj=0;jj<naxes[1];jj++) {
   for (ii=0;ii<naxes[0];ii++) {
     *(*(*(datap+0)+jj)+ii) = *(*(ppix+jj)+ii);
     *(*(*(datar+0)+jj)+ii) = *(*(presp+jj)+ii);
   }
 }
  
 drlft3(datap,speqp,1,N2,N3,1);
 drlft3(datar,speqr,1,N2,N3,1);

 fac=2.0/(1*N2*N3);
 sp1 = &datap[0][0][0];
 sp2 = &datar[0][0][0];
 for (j=0;j<1*N2*N3/2;j++) {
   r = sp1[0]*sp2[0] - sp1[1]*sp2[1];
   i = sp1[0]*sp2[1] + sp1[1]*sp2[0];
   sp1[0] = fac*r;
   sp1[1] = fac*i;
   sp1 += 2;
   sp2 += 2;
 }
 sp1 = &speqp[0][0];
 sp2 = &speqr[0][0];
 for (j=0; j<1*N2; j++) {
   r = sp1[0]*sp2[0] - sp1[1]*sp2[1];
   i = sp1[0]*sp2[1] + sp1[1]*sp2[0];
   sp1[0] = fac*r;
   sp1[1] = fac*i;
   sp1 += 2;
   sp2 += 2;
 }
 drlft3(datap,speqp,1,N2,N3,-1);
 
 for (jj=0;jj<naxes[1];jj++) {
   for (ii=0;ii<naxes[0];ii++) {
     *(*(ppix+jj)+ii) = *(*(*(datap)+jj)+ii);
   }
 }
 
 create_image( "!testconv.fits", ppix, naxes, headers, nheaders );

 free_dmatrix(ppix);
 free_dmatrix(presp);
 free_dcube(datap);
 free_dcube(datar);

 exit(0);
}
