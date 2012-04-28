/* Function : gcf */
/* Version : 1.0.0 */
/*   From NR.
 *
 * Returns the incomplete gamma function Q(a,x) evaluated by its continued
 * fraction representation as gammcf.  Also returns lnGamma(a) as gln.
 *
 * Calling gcf
 *   gcf(&gammcf, a, x, &gln);
 *
 * Needs:
 *   %%%libKLutil%%%
 */

#include "./KLfunc.h"	/* for gammln() */
#include <KLutil.h>	/* for rterror() */
#include <math.h>
#include <stdio.h>

#define ITMAX 1000
#define EPS 3.0e-7
#define FPMIN 1.0e-30

void gcf(float *gammcf, float a, float x, float *gln)
{
 int i;
 float an,b,c,d,del,h;
 
 *gln=gammln(a);
 b=x+1.0-a;
 c=1.0/FPMIN;
 d=1.0/b;
 h=d;
 for (i=1;i<=ITMAX;i++) {
    an = -i*(i-a);
    b += 2.0;
    d=an*d+b;
    if (fabs(d) < FPMIN) d=FPMIN;
    c=b+an/c;
    if (fabs(c) < FPMIN) c=FPMIN;
    d=1.0/d;
    del=d*c;
    h *= del;
    if (fabs(del-1.0) < EPS) break;
 }
 if (i > ITMAX) rterror("a too large, ITMAX too small in gcf");
 *gammcf=exp(-x+a*log(x)-(*gln))*h;

}
