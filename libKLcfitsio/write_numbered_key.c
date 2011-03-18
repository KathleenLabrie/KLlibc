/* Function: write_numbered_key */
/* Version: 1.0.1
 *	Appends a numbered key/value pair in a FITS header.  The root of the
 *	key is given as input.  Finds the next numbered key.
 *	Eg. If root is MOD, and MOD1 already exist, key will be MOD2.
 *
 * int write_numbered_key( char filename[], char keyword[], char value[],
 *		char type[], char comment[]);
 *
 * Arguments:
 *	Input: Name of the FITS file		- char filename[]
 *	       Root of the keyword		- char keyword[]
 *	       Value as a string		- char value[]
 *	       Value's type (string)		- char type[]
 *	       Comment              		- char comment[]
 *
 * Output:
 *	Error code: 0 if no error; 1+ if error;
 *
 * Calling write_key
 *	status = write_key(filename, keyword, value, type, comment);
 *
 * Needs
 *  %%%/astro/labrie/progc/img/fits/write_key.c%%%
 *  %%%-I/astro/labrie/progc/include%%%
 *  %%%-L/astro/labrie/progc/lib%%%
 *  %%%-lcfitsio%%%
 *  %%%-lm%%%
 *
 */

#include "./KLcfitsio.h"
#include <fitsio.h>
#include <mydef.h>		/* for MAXLENGTH */

int write_numbered_key( char filename[], char keyword[], char value[],
		char type[], char comment[])
{
 fitsfile *fptr;
 int status=0, index;
 char key[MAXLENGTH], junkstr[MAXLENGTH], junkcomment[MAXLENGTH];

 /* open FITS file */
 if ( fits_open_file(&fptr, filename, READONLY, &status) )
 	return( status );

 /* find index of next key */
 index=1;
 sprintf(key, "%s%d", keyword,index);
 while ( 
     (status = fits_read_keyword( fptr, key, junkstr, junkcomment, &status))
     != 
     KEY_NO_EXIST
   ) {
   index++;
   sprintf(key, "%s%d", keyword,index);
 }  /* found new index, end while loop */
 status=0;		/* reset status */
 
 /* close FITS file */
 if ( status = fits_close_file(fptr, &status) )
 	return( status );

 /* write key */
 if ( status = write_key( filename, key, value, type, comment ) )
 	return( status );

 return(0);
}
