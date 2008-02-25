/* Function : gser */
/* Version : 1.0.0 */
/*   From NR.
 *
 * Returns the incomplete gamma function P(a,x) evaluated by its series
 * representation a gamser.  Also returns lnGamma(a) as gln.
 *
 * Calling gser
 *   gser(&gamser, a, x, &gln);
 *
 * Needs:
 *   %%%libKLutil%%%
 */

#include "./KLfunc.h"	/* for gammln() */
#include <KLutil.h>	/* for rterror() */
#include <math.h>

#define ITMAX 1000
#define EPS 3.0e-7

void gser(float *gamser, float a, float x, float *gln)
{
 int n;
 float sum,del,ap;

 *gln=gammln(a);
 if (x <= 0.0) {
    if (x < 0.0) rterror("x less than 0 in routine gser");
    *gamser=0.0;
    return;
 } else {
    ap=a;
    del=sum=1.0/a;
    for (n=1;n<=ITMAX;n++) {
       ++ap;
       del *= x/ap;
       sum += del;
       if (fabs(del) < fabs(sum)*EPS) {
          *gamser=sum*exp(-x+a*log(x)-(*gln));
	  return;
       }
    }
    rterror("a too large, ITMAX too small in routine gser");
    return;
 }
}
