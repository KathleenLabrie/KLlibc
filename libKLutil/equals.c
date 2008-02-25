/* Function : equals */
/* Version : 0.1.0 */

#include <float.h>
#include <stdio.h>

int equals(double val1, double val2)
{
 double ratio;
 char strratio[80];

 ratio = val2/val1;
 sprintf(strratio,"%f",ratio);

 if ( !strncmp("nan",strratio,3) ) { /* both a zero */
 	return(1);
 } else if ( !strncmp("inf",strratio,3) ) { /* divide by zero, not equals */
 	return(0);
 } else {
 	if ( (ratio >= 1.-DBL_EPSILON) && (ratio <= 1.+DBL_EPSILON) ) {
		/* equals within double precision */
		return(1);
	}
 }

 return(0);
}
