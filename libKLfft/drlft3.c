/* Function : drlft3 */
/* Version: 1.0.0 */
/*   From NR.  Converted to double precision and to 0-arrays
 *
 * Given a three-dimensional real array data[0..nn1-1][0..nn2-1][0..nn3-1]
 * (where nn1 = 1 for the case of a logically two-dimensional array), this
 * routine returns (for isign=1) the complex fast Fourier transform as 
 * two complex arrays: On output, data contains the zero and positive
 * frequency values of the third frequency component, while
 * speq[0..nn1-1][0..2*nn2-1] contains the Nyquist critical frequency values
 * of the third frequency component.  First (and second) frequency components
 * are strored for zero, positive, and negative frequencies, in standard
 * wrap-around order.  See text for description of how complex values are
 * arranged.  For isign=-1, the inverse transform (times nn1*nn2*nn3/2 as a
 * constant multiplicative factor) is performed, with output data (viewed as
 * a real array) deriving from input data (viewed as complex) and speq.  The
 * dimensions nn1, nn2, nn3 must always be integer powers of 2.
 *
 * Needs:
 *   %%%libKLutil%%%
 */

#include "./KLfft.h"
#include <KLutil.h>	/* for rterror() */
#include <math.h>

void drlft3(double ***data, double **speq, unsigned long nn1,
			unsigned long nn2, unsigned long nn3, int isign)
{
 unsigned long i1,i2,i3,j1,j2,j3,nn[3],ii3;
 double theta,wi,wpi,wpr,wr,wtemp;
 double c1,c2,h1r,h1i,h2r,h2i;

 if (1+&data[nn1-1][nn2-1][nn3-1]-&data[0][0][0] != nn1*nn2*nn3)
    rterror("drlft3: problem with dimensions or contiguity of data array\n");
 c1=0.5;
 c2 = -0.5*isign;
 theta=isign*(6.28318530717959/nn3);
 wtemp=sin(0.5*theta);
 wpr = -2.0*wtemp*wtemp;
 wpi=sin(theta);
 nn[0]=nn1;
 nn[1]=nn2;
 nn[2]=nn3 >> 1;
 if (isign == 1) {
    dfourn(&data[0][0][0],nn,3,isign);
    for (i1=0;i1<nn1;i1++) {
       for (i2=0,j2=0;i2<nn2;i2++) {
          speq[i1][j2++]=data[i1][i2][0];
	  speq[i1][j2++]=data[i1][i2][1];
       }
    }
 }
 for (i1=0;i1<nn1;i1++) {
    j1=(i1 != 0 ? nn1-(i1+1)+1 : 0);
    wr=1.0;
    wi=0.0;
    for (ii3=0,i3=0;i3<(nn3>>2)+1;i3++,ii3+=2) {
       for (i2=0;i2<nn2;i2++) {
          if (i3 == 0) {
	     j2 = (i2 != 0 ? ((nn2-(i2+1))<<1)+2 : 0);
	     h1r=c1*(data[i1][i2][0]+speq[j1][j2]);
	     h1i=c1*(data[i1][i2][1]-speq[j1][j2+1]);
	     h2i=c2*(data[i1][i2][0]-speq[j1][j2]);
	     h2r=-c2*(data[i1][i2][1]+speq[j1][j2+1]);
	     data[i1][i2][0]=h1r+h2r;
	     data[i1][i2][1]=h1i+h2i;
	     speq[j1][j2]=h1r-h2r;
	     speq[j1][j2+1]=h2i-h1i;
	  } else {
	     j2 = (i2 != 0 ? nn2-(i2+1)+1 : 0);
	     j3 = nn3+2-((i3+1)<<1);
	     h1r=c1*(data[i1][i2][ii3]+data[j1][j2][j3]);
	     h1i=c1*(data[i1][i2][ii3+1]-data[j1][j2][j3+1]);
	     h2i=c2*(data[i1][i2][ii3]-data[j1][j2][j3]);
	     h2r=-c2*(data[i1][i2][ii3+1]+data[j1][j2][j3+1]);
	     data[i1][i2][ii3]=h1r+wr*h2r-wi*h2i;
	     data[i1][i2][ii3+1]=h1i+wr*h2i+wi*h2r;
	     data[j1][j2][j3]=h1r-wr*h2r+wi*h2i;
	     data[j1][j2][j3+1]=-h1i+wr*h2i+wi*h2r;
	  }
       }
       wr=(wtemp=wr)*wpr-wi*wpi+wr;
       wi=wi*wpr+wtemp*wpi+wi;
    }
 }
 if (isign == -1)
    dfourn(&data[0][0][0],nn,3,isign);
}
