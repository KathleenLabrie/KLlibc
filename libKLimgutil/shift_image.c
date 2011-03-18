/* Function : shift_image */
/* Version: 1.0.0 */
/*   Applies a x and y shift to a set of pixels-values contained in
 *   a 2-D array (pix[jj][ii] = value(ii,jj)).  The original dimensions are
 *   kept and 0 values are used for padding.  Returns a new 2-D array
 *   (pix[jj+djj][ii+dii] = value(ii,jj)).  Also returns an error code.
 *
 * int shift_image( double **ppix, unsigned long naxes[], long dii, long djj )
 *
 * Arguments :
 *   Input : 2-D array (pix[jj][ii] = value)	  - double **ppix
 *	     Length of each axis (ii,jj)		  - long naxes[]
 *	     Shift in ii				  - long dii
 *	     Shift in jj				  - long djj
 *   Output : shifted 2-D array (pix[jj+djj][ii+dii] = value) - **ppix
 *
 * Output :
 *   Error code : 0 if no error; 1 if error;
 *
 * Calling shift_image
 *   status = shift_image(array, naxes, dii, djj);
 *
 * Needs :
 *   %%%libKLutil%%%
 */

#include <myutil.h>
#include <stdio.h>
#include <stddef.h>

int shift_image( double **ppix, unsigned long naxes[], long dii, long djj )
{
 long ii, jj, kk, ll;
 double **newppix=NULL;

 printf("Shifting image ... ");
 fflush(stdout);

 /* Allocate memory for a temporary array and initialize to zero*/
 newppix = dmatrixc((long)naxes[1],(long)naxes[0]);

 /* Shift */
 for (jj=0; jj<naxes[1]; jj++) {
   for (ii=0; ii<naxes[0]; ii++) {
     kk=ii+dii;
     ll=jj+djj;
     if ((kk>=0) && (kk<naxes[0]) && (ll>=0) && (ll<naxes[1])) {
       if ((ii == naxes[0]) || (jj == naxes[1])) { /* Outside allocated memory*/
         printf("Error: Segmentation fault (newppix)\n");
	 return(111);
       } 
       *(*(newppix + ll) + kk) = *(*(ppix + jj) + ii);
     }
   }
 }
 
 /* Copy newppix to ppix */
 for (jj=0; jj<naxes[1]; jj++) {
   for (ii=0; ii<naxes[0]; ii++) {
     *(*(ppix + jj) + ii) = *(*(newppix + jj) + ii);
   }
 }

 free_dmatrix(newppix);
 printf("done\n");

 return(0);
}
