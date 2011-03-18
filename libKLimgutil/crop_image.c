/* Function: crop_image */
/* Version: 1.0.0 */
/*	Crop a 2-D array.
 *
 * int crop_image( double **ppix, unsigned long section[], > double **pcrop)
 *
 * Arguments :
 *   Input:	2-D array (pix[jj][ii] = value)	- double **ppix
 *		Section (x1,x2,y1,y2)		- unsigned long section[]
 *   Output:	Cropped section of the image	- double **pcrop
 *
 * Output :
 *   Error code: 0 if no error; 1 if error;
 *
 * Calling crop_image
 *   status = crop_image(array, section, &cropped);
 *
 * Needs:
 *   %%%libKLutil%%%
 */

#include <myutil.h>
#include <stdio.h>
#include <stddef.h>

int crop_image( double **ppix, unsigned long section[], double **pcrop )
{
 unsigned long ii, jj, kk, ll;
 unsigned long naxes_crop[2];

 printf("Cropping section [%d:%d,%d:%d] ... ",section[0],section[1],section[2],
 		section[3]);
 fflush(stdout);
 
 /* Deduce axis length */
 naxes_crop[0] = section[1]-section[0] + 1;
 naxes_crop[1] = section[3]-section[2] + 1;

 /* Allocate memory for pcrop if not defined yet */
 if (pcrop == NULL) {
   pcrop = dmatrix((long)naxes_crop[1],(long)naxes_crop[0]);
 }

 /* Crop */
 kk=ll=0;
 for (jj=section[2]-1; jj<section[3]; jj++) {
   for (ii=section[0]-1; ii<section[1]; ii++) {
     *(*(pcrop + ll) + kk) = *(*(ppix + jj) + ii);
     kk++;
   }
   kk=0;
   ll++;
 }

 return(0);
}
