/* Function : edit_image
 * Version : 1.2.1
 *   Opens a FITS file (new for now) and writes a 2-D array in it
 *   (pix[y][x] = value).  Returns an error code.  In new image mode
 *   the header of the original image is copied.
 *
 * int edit_image( char filename[], char newfilename[], double **ppix )
 *
 * Arguments :
 *   Input : Name of original FITS file		- char filename[]
 *	      Name of new FITS file			- char newfilename[]
 *	      2-D array (pix[y][x] = value)	- **ppix
 *
 * Output :
 *   Error code : 0 if no error; 1+ if error;
 *
 * Calling edit_image
 *  status = edit_image(filename, newfilename, array);
 *
 * Needs the cfitsio library.
 *	/astro/labrie/progc/img/fits/printerror.o
 *	/astro/labrie/progc/general/headers/myutil.o
 *	-I/astro/labrie/progc/include -L/astro/labrie/progc/lib
 *
 * Modes : create new image or overwrite (if newfilename eq filename)
 *
 */

#include "./KLcfitsio.h"
#include <stdio.h>
#include <fitsio.h>
#include <mydef.h>
#include <mytime.h>
#include <string.h>

int edit_image(char filename[], char newfilename[], double **ppix )
{
 fitsfile *fptr, *newfptr;
 int status, nfound, day, month, year, timeref;
 int naxis = 2;			/* 2-dimensional image */
 int bitpix = DOUBLE_IMG;		/* Output image type is double */
 int datatype = TDOUBLE;
 long naxes[2];			/* dimensions of the image */
 long fpixel, npixels;
 char date[FLEN_VALUE], time[FLEN_VALUE];
 char *nullcomment;
 char outfilename[MAXLENGTH];

 nullcomment=0;

  /***********************************************************************/
  status = 0;		/* Initialize status before calling fitsio routines */
  /***********************************************************************/

 /* Copy newfilename to outfilename.  'newfilename' is passed has a reference,
  * therefore any change to it will be passed back to the calling routine
  * which is not really what one wants.  (as I discovered...)
  * The addition of the '!' is meaningful here but not necessarly useful in
  * the calling routine. */
 if (!strcmp(newfilename,filename)) {
   strcpy(outfilename,"!");
   strcat(outfilename,filename);
 }
 else {
   strcpy(outfilename,newfilename);
 }
 printf("Writing %s ... ",newfilename);
 fflush(stdout);

/* Open the existing FITS file */
 if ( fits_open_file(&fptr, filename, READONLY, &status) )
 	printerror( status );

/* Create the new FITS file  (should I use a template?)*/
 if ( fits_create_file(&newfptr, outfilename, &status) )
 	printerror( status );

 /* No need to create an image in the new FITS file because the primary
  * array is automatically created when the header is copied */

/* Copy the header from the existing FITS file to the new FITS file */
 if ( fits_copy_header(fptr, newfptr, &status) )
 	printerror( status );
 
/* Get the length of the axes */
 if ( fits_read_keys_lng(newfptr, "NAXIS", 1, 2, naxes, &nfound, &status) )
 	printerror( status );

/* Write the image (array of pixel values) in the new FITS file */
 fpixel = 1;				/* first pixel to write */
 npixels = naxes[0] * naxes[1];	/* number of pixels to write */

 if ( fits_write_img(newfptr, datatype, fpixel, npixels, ppix[0], &status) )
 	printerror( status );

/* Edit header */
 if ( fits_get_system_date(&day, &month, &year, &status) )
 	printerror( status );
 if ( fits_date2str(year, month, day, date, &status) )
 	printerror( status );
 if ( fits_update_key(newfptr, TSTRING, "DATE", date, "", &status) )
 	printerror( status );

 if ( fits_get_system_time(time, &timeref, &status) )
 	printerror( status );
 if ( timeref == 0 )		/* Convert UTC/GMT to Local time */
 	if ( utc2local(time, FITS_FMT) ) {
		printf("Error : Unable to convert time.\n");
		exit(1);
	} 
 if ( status = cnvtimefmt(time, FITS_FMT, IRAF_FMT))
 	printerror( status ); 	/* Stupid IRAF cannot read the new FITS
 					 *  date-time Y2K format */
 if ( fits_update_key(newfptr, TSTRING, "IRAF-TLM", time, nullcomment, &status) )
 	printerror( status );
 
/* Close the existing FITS file */
 if ( fits_close_file(fptr, &status) )
 	printerror( status );

/* Close the new FITS file */
 if ( fits_close_file(newfptr, &status) )
 	printerror( status );

 printf("done\n");

 return(0);
}
