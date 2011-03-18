/* Main: findkey */
/* Version: 1.0.0 */
/*	Tell whether or not the keyword is found in the header.
 *
 * Usage: findkey [-v] image keyword
 *
 * Arguments:
 *	image:		name of the image
 *	keyword:	name of the keyword
 *	-v:		KVERBOSE on
 *
 * Output:
 *	system outputs: 202 -> not found
 *			  0 -> found
 *
 * Needs:
 *	The cfitsio library ( -lcfitsio )
 *	The math library ( -lm )	fitsio needs it
 *	/astro/labrie/progc/img/fits/printerror.o
 *	/astro/labrie/progc/img/fits/printwarning.o
 *	-L/astro/labrie/progc/lib
 *	-I/astro/labrie/progc/include
 */

#include "./KLimghead.h"
#include <KLcfitsio.h>
#include <KLutil.h>
#include <fitsio.h>
#include <stdio.h>
#include <string.h>

main(argc,argv)
int argc;
char *argv[];
{
 char keyword[KEYLENGTH],comment[CMTLENGTH], strvalue[VALLENGTH];
 char image[MAXLENGTH];
 int status=0, FLAGS=0;
 
 /* Read command line */
 while (--argc > 2) {
   *++argv;
   if (!strncmp("-v",*argv,2)) {
     FLAGS |= 1 << VERBOSE;
   }
 }
 strcpy(image,*++argv);
 strcpy(keyword,*++argv);

 if (status = read_keyword(image, keyword, strvalue, comment)) {
 	if (status == KEY_NO_EXIST) {
	  if (FLAGS & 1 << VERBOSE) printwarning( status );
        }
 }
 else if (status) {
 	printerror(status);
 }
 else {
   if (FLAGS & 1 << VERBOSE) { 
   	printf("Keyword '%s' found in image '%s'\n",keyword,image);
   }
 }
 
 exit(status);
}
	  
