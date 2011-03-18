/* Main : mask2img */
/* Version: 1.0.0 */
/*   Create an image from a mask data file
 *
 * Usage: mask2img inmask outimg naxes0 naxes1 imgtitle
 *
 *	inmask		: mask  ( x,y coordinates of the mask )
 *	outimg		: name of the output image
 *	naxes0		: length of the X axis
 *	naxes1		: length of the Y axis
 *	imgtitle	: Title of the output image
 *
 * Needs
 *   %%%libKLimgutil%%%
 *   %%%libKLcfitsio%%%
 *   %%%libKLutil%%%
 *   %%%libKLfile%%%
 */

#include "./KLimgutil.h"
#include <KLutil.h>
#include <KLfile.h>
#include <KLcfitsio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#define NHEADERS 1

main (argc,argv)
int argc;
char *argv[];
{
 int status,i;
 long ncoo;
 double *xcoo=NULL, *ycoo=NULL;
 double **pcoo=NULL,**mask=NULL;
 KLFITS_HEADER *headers=NULL;
 
 long naxes[2];
 char imgtitle[MAXLENGTH];
 char maskname[MAXLENGTH], imgname[MAXLENGTH];
 
 status = 0;
 
 /* Read command line */
 strcpy(maskname,argv[1]);
 strcpy(imgname,argv[2]);
 naxes[0] = atoi(argv[3]);
 naxes[1] = atoi(argv[4]);
 strcpy(imgtitle,argv[5]);
 
 /* Read mask */
 if (status = rd_set_double(maskname, &xcoo, &ycoo, &ncoo) != 0) {
 	if (xcoo != NULL) free_dvector(xcoo);
	if (ycoo != NULL) free_dvector(ycoo);
	exit(status);
 }
 pcoo = dmatrix(ncoo,2);
 for (i=0;i<ncoo;i++) {
   *(*(pcoo+i)+0) = *(xcoo+i)-1;
   *(*(pcoo+i)+1) = *(ycoo+i)-1;
 }
 free_dvector(xcoo);
 free_dvector(ycoo);
 
 /* Convert mask to img array */
 if (status = make_mask(pcoo, ncoo, naxes, &mask) != 0) {
 	if (pcoo != NULL) free_dmatrix(pcoo);
	if (mask != NULL) free_dmatrix(mask);
	exit(status);
 }
 free_dmatrix(pcoo);

 /* Define header entries */
 headers = klfits_header_vector(NHEADERS);
 strcpy(headers[0].keyword,"title");
 strcpy(headers[0].value_str, imgtitle);
 headers[0].datatype = TSTRING;

 /* Create mask img */
 if (status = create_image( imgname, mask, naxes, headers, NHEADERS) != 0) {
 	if (mask != NULL) free_dmatrix(mask);
	exit(status);
 }

 exit(0);
}
