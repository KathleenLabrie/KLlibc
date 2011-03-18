/* Function : make_mask */
/* Version: 1.0.1 */
/*   From a list of coordinates (pcoo[i][axis]) create a 
 *   naxes[0] by naxes[1] array filled with zeros except at the
 *   positions found in the list.
 *
 * int make_mask(double **pcoo, unsigned long npts, long naxes[], 
 *		    > double ***ptr2mask);
 *
 * Arguments :
 *   Inputs : List of coordinates (pcoo[i][axis]) - double **pcoo
 *		Number of points			 - unsigned long *npts
 *		Length of the axes			 - long naxes[]
 *   Output : Pointer to a 2-D mask array		 - double ***ptr2mask
 *
 * Output :
 *   Error code : 0 if no error; 1 if error;
 *
 * Calling make_mask
 *   status = make_mask(pcoo,npts,naxes,&mask);
 *
 * Needs :
 *   %%%libKLutil%%%
 */

#include <myutil.h>
#include <stdio.h>

int make_mask(double **pcoo, unsigned long npts, long naxes[], 
		double ***ptr2mask)
{
 long ii,jj,n;

 printf("Creating a 2-D representation of the mask ... ");
 fflush(stdout);

 *ptr2mask = dmatrix(naxes[1],naxes[0]);
 for (jj=0;jj<naxes[1];jj++) {
   for (ii=0;ii<naxes[0];ii++) {
     *(*(*ptr2mask + jj) + ii) = 0.;
   }
 }
 
 for (n=0; n<npts; n++) {
   ii = (int)*(*(pcoo+n) + 0);
   jj = (int)*(*(pcoo+n) + 1);
   if ((ii >= 0) && (jj >= 0) && (ii < naxes[0]) && (jj < naxes[1]))
     *(*(*ptr2mask + jj) + ii) = 1.;
 }
 printf("done\n");

 return(0);
}
