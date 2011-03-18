/* Function: write_key */
/* Version: 1.0.1 */
/*	Append or update a key/value pair in a FITS header
 *
 * int write_key(char filename[], char keyword[], char value[], char type[], 
 *		char comment[]);
 * Arguments:
 *   Input: Name of the FITS file		- char filename[]
 *          Name of the keyword		- char keyword[]
 *          Value as a string		- char value[]
 *          Value's type (string)		- char type[]
 *          Comment				- char comment[]
 *
 * Output:
 *   Error code: 0 if no error; 1+ if error;
 *
 * Calling write_key
 *   status = write_key(filename, keyword, value, type, comment);
 *
 * Needs the cfitsio library.
 *	/astro/labrie/progc/img/fits/printerror.o
 *	/astro/labrie/progc/img/fits/get_type.o
 *	-I/astro/labrie/progc/include -L/astro/labrie/progc/lib
 *
 */

#include "./KLcfitsio.h"
#include <fitsio.h>
#include <stdlib.h>	/* for atoi, atof */

int write_key(char filename[], char keyword[], char value[], char type[], 
 		char comment[])
{
 fitsfile *fptr;
 int status=0;
 int datatype;
 int ivalue;
 float fvalue;
 double dvalue;

 /* transform type to cfitsio code */
 datatype = get_type(type);

 /* open FITS file */
 if ( fits_open_file(&fptr, filename, READWRITE, &status) )
 	printerror( status );

 /* write entry */
 switch (datatype) {
   case TSTRING:
   	if ( fits_update_key(fptr, datatype, keyword, value, comment, &status) )
 		printerror( status );
	break;

   case TINT:
       ivalue = atoi(value);
       if ( fits_update_key(fptr, datatype, keyword, &ivalue, comment, &status) )
		printerror( status );
   	break;

   case TFLOAT:
       fvalue = (float)atof(value);
   	if ( fits_update_key(fptr, datatype, keyword, &fvalue, comment, &status) )
		printerror( status );
   	break;

   case TDOUBLE:
   	dvalue = atof(value);
       if ( fits_update_key(fptr, datatype, keyword, &dvalue, comment, &status) )
		printerror( status );
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

