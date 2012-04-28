/* Function : factrl */
/* Version : 1.0.0 */
/*   Returns the value n! as a floating-point number
 *
 * Needs:
 *   %%%libKLutil%%%
 */

#include "./KLfunc.h"
#include <myutil.h>
#include <math.h>

float factrl(int n)
{
 static int ntop=4;
 static float a[33]={1.0,1.0,2.0,6.0,24.0};
 int j;
 
 if (n < 0) rterror("Negative factorial in routine factrl");
 if (n > 32) return exp(gammln(n+1.0));
 while (ntop<n) {
    j=ntop++;
    a[ntop]=a[j]*ntop;
 }

 return a[n];
}
