/* Function: mulImage */
/* Version: 1.0.1 
 * 	Multiply one image or section by some value.
 *
 * int mulImage(double **ppix1, double value, double **presult,
 *	unsigned long naxes[], unsigned long section[]);
 *
 * Arguments :
 *	Inputs :
 *		Image 1		- double **ppix1 (ppix1[naxes[1]][naxes[0]])
 *		Second operand	- double value
 *		Size of image 1 & 2	- unsigned long naxes[] (0->x; 1->y)
 *		Section to use	- unsigned long section[] (x1,x2,y1,y2)
 *	Output :
 *		Output image		- double **presult 
 *					  (presult[section[3]-section[2]]
 *						   [section[1]-section[0]])
 *
 * Output :
 *	Error code : 0 if no error; 1 if error;
 *
 * Calling mulImage
 *	status = mulImage(ppix1, value, presult, naxes, section);
 *
 * Needs :
 */

#include "./KLimgmath.h"

int mulImage(double **ppix1, double value, double **presult,
	long naxes[], unsigned long section[])
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

 /* Multiply */
 for (jj=section[2]-1,ll=0; jj<section[3]; jj++,ll++) {
   for (ii=section[0]-1,kk=0; ii<section[1]; ii++,kk++) {
       *(*(presult+ll)+kk) = *(*(ppix1+jj)+ii) * value;
   }
 }

 return(0);
}
