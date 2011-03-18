/* Function: modify_key */
/* Version: 1.0.0 */
/*	Modify the value of a FITS header keyword
 *
 * int modify_key(char filename[], char old_keyword[], char new_keyword[]);
 *
 * Arguments:
 *   Input: Name of the FITS file	- char filename[]
 *          Name of the old keyword	- char old_keyword[]
 *          Name of the new keyword	- char new_keyword[]
 *
 * Output:
 *   Error code: 0 if no error; 1+ if error;
 *
 * Calling modify_key
 *   status = modify_key(filename, old_key, new_key);
 *
 * Needs:
 *   %%%libcfitsio%%%
 */

#include "./KLcfitsio.h"
#include <fitsio.h>

int modify_key(char filename[], char old_keyword[], char new_keyword[])
{
 fitsfile *fptr;
 int status=0;

 /* open FITS file */
 if ( fits_open_file(&fptr, filename, READWRITE, &status) )
 	printerror( status );

 /* modify keyword */
 if ( fits_modify_name(fptr, old_keyword, new_keyword, &status) ) {
 	if (status == 202) {
		printf("\n%s:\t", filename);
		fflush(stdout);
		printwarning( status );
	}
	else {
		printerror( status );
	}
 }

 /* close file */
 if ( fits_close_file(fptr, &status) )
 	printerror( status );

 return(status);
}
