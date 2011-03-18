/* Function : read_points */
/* Version: 1.0.0 */
/*   Reads a list of  x,y coordinates from a file created with
 *   IRAF's rimcursor.  Shift can be applied.
 *
 * int read_points(char file[], double ***ptr2pcoo, unsigned long *npts,
 *		     long dx, long dy)
 *
 * Arguments :
 *   Inputs : List of coordinates (x y str str)	- char file[]
 *		Number of points			- unsigned long *npts
 *		Shift in x				- long dx
 *		Shift in y				- long dy
 *   Output : Pointer to 2-D list of pts (pcoo[i][axis]) - double ***ptr2pcoo
 *
 * Output :
 *   Error code : 0 if no error; 1 if error;
 *
 * Calling read_points
 *   status = read_points(file,&pcoo,&npts,dx,dy);
 *
 * Needs :
 *   %%%libKLutil%%%
 */

#include "./KLimgutil.h"
#include <KLutil.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define MAXNCOL 4

int read_points( char filename[], double ***ptr2pcoo, unsigned long *npts,
                 long dx, long dy )
{
 unsigned long i=0;
 double x[MAXNBPT],y[MAXNBPT];
 char line[MAXLENGTH], **p_lines;  /* token=\s+ */
 FILE *fp;

 printf("Reading points in %s ... ", filename);
 p_lines = svector(MAXNCOL, MAXLENGTH);
 fflush(stdout);
 if ((fp = fopen( filename, "r" )) == NULL)
 	return(FILE_NOT_OPENED);
 while (fgets( line, MAXLENGTH, fp) != NULL) {
   splitstr(line, p_lines, SPACES);
   x[i] = atof(p_lines[0]);
   y[i++] = atof(p_lines[1]);
   if (i==MAXNBPT) { return(ARRAY_TOO_BIG); }
 }
 fclose(fp);

 *npts=i;

 *ptr2pcoo = dmatrix(*npts,2);
 for (i=0;i<*npts;i++) {
   *(*(*ptr2pcoo + i) + 0) = x[i]-1 + dx;
   *(*(*ptr2pcoo + i) + 1) = y[i]-1 + dy;
 }

 printf("done\n");
 fflush(stdout);

 return(0);
}
