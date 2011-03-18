/* Function: read_key */
/* Version: 1.0.1 */
/*	Read the value of a FITS header keyword
 *
 * int read_key(char filename[], char keyword[], > char value[], char type[],
 *		> char comments[]);
 *
 * Arguments:
 *   Input: Name of the FITS file		- char filename[]
 *          Name of the keyword		- char keyword[]
 *          Value;s type (string)		- char type[]
 *
 *   Output: Value as a string		- char value[]
 *           Comment				- char comment[]
 *
 * Output:
 *   Error code: 0 if no error; 1+ if error;
 *
 * Calling read_key
 *   status = read_key(filename, keyword, value, type, comment);
 *
 * Needs the cfitsio library.
 *	/astro/labrie/progc/img/fits/printerror.o
 *	/astro/labrie/progc/img/fits/get_type.o
 *	-I/astro/labrie/progc/include -L/astro/labrie/progc/lib
 *
 */

#include "./KLcfitsio.h"
#include <fitsio.h>

int read_key(char filename[], char keyword[], char value[], char type[],
		char comment[])
{
 fitsfile *fptr;
 int status=0;
 int datatype;
 unsigned short usvalue;
 int ivalue;
 float fvalue;
 double dvalue;

 /* transform type to cfitsio code */
 datatype = get_type(type);

 /* open FITS file */
 if ( fits_open_file(&fptr, filename, READONLY, &status) )
 	printerror( status );

 /* read entry */
 switch (datatype) {
   case TSTRING:
   	if ( fits_read_key(fptr, datatype, keyword, value, comment, &status) )
		printerror( status );
	break;
   case TUSHORT:
   	if ( fits_read_key(fptr, datatype, keyword, &usvalue, comment, &status) )
		printerror( status );
	sprintf(value,"%d",usvalue);
	break;
   case TINT:
   	if ( fits_read_key(fptr, datatype, keyword, &ivalue, comment, &status) )
		printerror( status );
	sprintf(value,"%d",ivalue);
	break;
   case TFLOAT:
   	if ( fits_read_key(fptr, datatype, keyword, &fvalue, comment, &status) )
		printerror( status );
	sprintf(value,"%f",fvalue);
	break;
   case TDOUBLE:
   	if ( fits_read_key(fptr, datatype, keyword, &dvalue, comment, &status) )
		printerror( status );
	sprintf(value,"%lf",dvalue);
	break;
   default:
   	printerror( BAD_DATATYPE );
	break;
 }

 /* close FITS file */
 if ( fits_close_file(fptr, &status) )
 	printerror( status );

 return(0);
}
