/* Function : findindex */
/* Version: 0.1.0 */

#include "./KLutil.h"	/* for error codes and equals() */
#include <stdio.h>	/* for stderr */

int findindex(double value, double *vec, long int n, long int *index)
{
 int status=0;
 long int i;
 
 for (i=0; i<n; i++ ) {
   if ( equals(value,*(vec+i)) ) { 
     *index=i;
     return(status);
   }
 }
 fprintf(stderr,"Index of %f not found\n",value);
 fprintf(stderr,ERRMSG_INTERNAL_ERROR);

 return(ERRNO_INTERNAL_ERROR);
}
