/* Function : create_image
 * Version : 1.1.2
 *   Create a FITS file and writes a 2-D array in it
 *   (pix[y][x] = value).  Returns an error code.  
 *
 * int create_image( char newfilename[], double **ppix, long naxes[],
 *		KLFITS_HEADER headers[], int nheaders )
 *
 * Arguments :
 *   Input : 
 *	      Name of new FITS file			- char newfilename[]
 *	      2-D array (pix[y][x] = value)	- **ppix
 *	      Size of the image			- long naxes[]
 *	      Header content				- KL_FITS_HEADER headers[]
 *
 * Output :
 *   Error code : 0 if no error; 1+ if error;
 *
 * Calling create_image
 *  status = create_image(newfilename, array, naxes, headers, nheaders);
 *
 * Needs:
 *  %%%libKLcfitsio%%%
 *  %%%libKLutil%%%
 *  %%%libcfitsio%%%
 */

#include "./KLcfitsio.h"
#include <stdio.h>
#include <fitsio.h>
#include <mydef.h>
#include <mytime.h>
#include <string.h>

int create_image(char newfilename[], double **ppix, long naxes[],
	KLFITS_HEADER headers[], int nheaders)
{
 int i;
 fitsfile *newfptr;
 int status, nfound, day, month, year, timeref;
 int naxis = 2;			/* 2-dimensional image */
 int bitpix = DOUBLE_IMG;		/* Output image type is double */
 int datatype = TDOUBLE;
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
 strcpy(outfilename,newfilename);
 printf("Writing %s ... ",newfilename);
 fflush(stdout);

/* Create the new FITS file  (should I use a template?)*/
 if ( fits_create_file(&newfptr, outfilename, &status) )
 	printerror( status );

/* Create a new primary array */
 if ( fits_create_img(newfptr, bitpix, naxis, naxes, &status) )
 	printerror( status );

/* Write the image (array of pixel values) in the new FITS file */
 fpixel = 1;				/* first pixel to write */
 npixels = naxes[0] * naxes[1];	/* number of pixels to write */

 if ( fits_write_img(newfptr, datatype, fpixel, npixels, ppix[0], &status) )
 	printerror( status );

/* Edit header */
 /*** Time setting ***/
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

 /*** Other headers ***/
 for (i=0; i<nheaders; i++) { klfits_update_key( newfptr, headers[i] ); }
  
/* Close the new FITS file */
 if ( fits_close_file(newfptr, &status) )
 	printerror( status );

 printf("done\n");

 return(0);
}
