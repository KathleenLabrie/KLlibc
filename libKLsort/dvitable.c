/* Function : vitable */
/* Version: 0.1.0 */
/*   Create an index table for a vector.
 *   Returns error status.
 *
 * int dvitable(double vmain[], unsigned long nmain, double vec[], 
 *		unsigned long nvec, double index[]);
 *
 * Needs
 *   %%%libKLutil%%%
 */

#include <KLutil.h>	/* for equals() */
#include <stdio.h>

int dvitable(double vmain[], unsigned long nmain, double vec[], 
		unsigned long nvec, unsigned long index[])
{
 int status=0;
 unsigned long i,j;
 int found;

 for (i=0;i<nvec;i++) {
   found=0;
   for (j=0;j<nmain;j++) {
     if ( equals(vmain[j],vec[i]) ) {
        index[i]=j;
	found=1;
     }
   }
   if (!found) {
     fprintf(stderr,ERRMSG_INTERNAL_ERROR);
     fprintf(stderr,"ERROR: In 'vitable'. Index for %g not found.\n",vec[i]);
     return(ERRNO_INTERNAL_ERROR);
   }
 }

 return(status);
}
