/* Function: read_keyword */
/* Version: 1.0.0 */
/*	Read the value of a FITS header keyword as a string no matter
 *	the datatype.  Outputs 202 if the keyword can not be found.
 *
 * int read_keyword(char filename[], char keyword[], > char value[], 
 *		> char comments[]);
 *
 * Arguments:
 *   Input: Name of the FITS file	- char filename[]
 *          Name of the keyword		- cahr keyword[]
 *
 *   Output: Value as a string		- char value[]
 *           Comment			- char comment[]
 *
 * Output:
 *   Error code: 0 if no error; 1+ if error (202 if keyword not found)
 *
 * Calling read_keyword
 *   status = read_keyword(filename, keyword, value, comment);
 *
 * Needs:
 *   %%%libcfitsio%%%
 */

#include "./KLcfitsio.h"
#include <fitsio.h>

int read_keyword(char filename[], char keyword[], char value[], char comment[])
{
 fitsfile *fptr;
 int status = 0;

 /* open FITS file */
 if ( fits_open_file(&fptr, filename, READONLY, &status) )
 	printerror( status );

 /* find keyword and read entry */
 if ( fits_read_keyword(fptr, keyword, value, comment, &status) )
 	if (status != KEY_NO_EXIST) printerror( status );

 /* close FITS file */
 if ( fits_close_file(fptr, &status) )
 	if (status != KEY_NO_EXIST) printerror( status );

 return(status);
}
