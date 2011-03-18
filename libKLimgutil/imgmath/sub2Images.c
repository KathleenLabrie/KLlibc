/* Function: sub2Images */
/* Version: 1.0.1 
 * 	Subtract one image or section from another.  A shift can be applied to 
 *	the second image before computation.  Note that if the shift is
 *	dx,dy the corresponding point is ii-dx, jj-dy.
 *	Eg.
 *	  Point on first image (100,100)
 *	  If shift on second image is (-50,-50) it means that
 *	  corresponding point in second image is at (150,150).
 *	  Therefore *(*(ppix2+100-(-50))+100-(-50)) or 
 *	  *(*(ppix2+jj-dy)+ii-dx).
 *
 * 	WARNING: no padding yet
 *
 * int sub2Images(double **ppix1, double **ppix2, double **presult,
 *	unsigned long naxes[], unsigned long section[], long dx, long dy);
 *
 * Arguments :
 *	Inputs :
 *		Image 1		- double **ppix1 (ppix1[naxes[1]][naxes[0]])
 *		Image 2		- double **ppix2 (ppix2[naxes[1]][naxes[0]])
 *		Size of image 1 & 2	- unsigned long naxes[] (0->x; 1->y)
 *		Section to use	- unsigned long section[] (x1,x2,y1,y2)
 *		Shift in x		- long dx
 *		Shift in y		- long dy
 *	Output :
 *		Output image		- double **presult 
 *					  (presult[section[3]-section[2]]
 *						   [section[1]-section[0]])
 *
 * Output :
 *	Error code : 0 if no error; 1 if error;
 *
 * Calling sub2Images
 *	status = sub2Images(ppix1, ppix2, presult, naxes, section, dx, dy);
 *
 * Needs :
 */

#include "./KLimgmath.h"

int sub2Images(double **ppix1, double **ppix2, double **presult,
	long naxes[], unsigned long section[], long dx, long dy)
{
 unsigned long ii, jj, kk, ll;
 
 /* Make section is within images limits */
 if ( (section[0]>section[1]) || (section[2]>section[3]) )
 	return(ILLEGAL_SECTION);
 /* Images 1 */
 if ( (section[0]<0) || (section[0]>naxes[0]) ) return(ILLEGAL_SECTION_XL);
 if ( (section[1]<0) || (section[1]>naxes[0]) ) return(ILLEGAL_SECTION_XH);
 if ( (section[2]<0) || (section[2]>naxes[1]) ) return(ILLEGAL_SECTION_YL);
 if ( (section[3]<0) || (section[3]>naxes[1]) ) return(ILLEGAL_SECTION_YH);

 /* Images 2 (have consider dx and dy) */
 if ( (section[0]+dx<0) || (section[0]+dx>naxes[0]) ) return(ILLEGAL_SECTION_XL);
 if ( (section[1]+dx<0) || (section[1]+dx>naxes[0]) ) return(ILLEGAL_SECTION_XH);
 if ( (section[2]+dy<0) || (section[2]+dy>naxes[1]) ) return(ILLEGAL_SECTION_YL);
 if ( (section[3]+dy<0) || (section[3]+dy>naxes[1]) ) return(ILLEGAL_SECTION_YH);

 /* Subtract */
 for (jj=section[2]-1,ll=0; jj<section[3]; jj++,ll++) {
   for (ii=section[0]-1,kk=0; ii<section[1]; ii++,kk++) {
       *(*(presult+ll)+kk) = *(*(ppix1+jj)+ii) - 
     			      *(*(ppix2+jj-dy)+ii-dx);
   }
 }

 return(0);
}
