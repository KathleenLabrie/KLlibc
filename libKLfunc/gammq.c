/* Function : gammq */
/* Version : 1.0.0 */
/*   From NR
 *
 * Returns the incomplete gamma function Q(a,x) = 1 - P(a,x).
 *
 * Calling gammq
 *   Q = gammq(a,x);
 *
 * Needs:
 *   %%%libKLutil%%%
 */

#include "./KLfunc.h"	/* for gcf(), gser() */
#include <KLutil.h>	/* for rterror() */

float gammq(float a, float x)
{
 float gamser,gammcf,gln;

 if (x < 0.0 || a <= 0.0) rterror("Invalid arguments in routine gammq");
 if (x < (a+1.0)) {
    gser(&gamser,a,x,&gln);
    return 1.0-gamser;
 } else {
    gcf(&gammcf,a,x,&gln);
    return gammcf;
 }
}
