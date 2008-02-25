/* Function : gamdev */
/* Version : 1.0.0 */
/*   From NR.
 *
 *   Returns a deviate distributed as a gamma distribution of integer order
 *   ia, i.e., a waiting time to the iath event in a Poisson process of 
 *   unit mean, using ran1(idum) as the source of uniform deviates.
 */

#include "./KLran.h"
#include <myutil.h>
#include <math.h>

float gamdev(int ia, long int *idum)
{
 int j;
 float am,e,s,v1,v2,x,y;
 
 if (ia < 1) rterror("Error in routine gamdev");
 if (ia < 6) {
    x=1.0;
    for (j=1;j<=ia;j++) x *= ran1(idum);
    x = -log(x);
 } else {
    do {
       do {
          do {
	     v1=2.0*ran1(idum)-1.0;
	     v2=2.0*ran1(idum)-1.0;
	  } while (v1*v1+v2*v2 > 1.0);
	  y=v2/v1;
	  am=ia-1;
	  s=sqrt(2.0*am+1.0);
	  x=s*y+am;
       } while (x <= 0.0);
       e=(1.0+y*y)*exp(am*log(x/am)-s*y);
    } while (ran1(idum) > e);
 }

 return x;
}
