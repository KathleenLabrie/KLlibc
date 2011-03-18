/* Function : read_image
 * Version: 1.0.3
 *   Open a FITS file and read it in to a 2-D array (pix[y][x] = value)
 *   Allocates memory for the array.  Returns the address of the pointer 
 *   to the array (argument) and an error code.
 *
 * int read_image( char filename[], > double ***ptr2ppix, long naxes[] )
 *
 * Arguments :
 *   Input : Name of FITS file
 *   Output (argument) : Address of the pointer to a 2-array containing the 
 *			  pixel values, pix[y][x]
 *			 Length of both axes, x & y, in naxes[2]
 * Output :
 *   Error code : 0 if no error; 1+ if error;
 *
 * Calling read_image
 *   status = read_image(filename, &array, naxes);
 *   The address of array (**array) is needed because ptr2ppix contains
 *   the address of the 2D array ppix (**ppix)
 *
 * Needs the cfitsio library. 
 *	/astro/labrie/progc/general/headers/myutil.o
 *	-I/astro/labrie/progc/include -L/astro/labrie/progc/lib
 */

#include "./KLcfitsio.h"
#include <fitsio.h>
#include <myutil.h>

#define buffsize 1000

int read_image( char filename[], double ***ptr2ppix, long naxes[] )
{
  fitsfile *fptr;		/* pointer to FITS file, defined in fitsio.h */
  int status, nfound, anynull;
  unsigned long npixels, nbuffer, first_element;
  unsigned long i,ii,jj;
  double nullval, buffer[buffsize];

  /***********************************************************************/
  status = 0;		/* Initialize status before calling fitsio routines */
  /***********************************************************************/
  ii=jj=0;

  printf("\nReading %s ... ",filename);

  if ( fits_open_file(&fptr, filename, READONLY, &status) )
  	printerror( status );

  /* read the NAXIS1 and NAXIS2 keyword to get image size */
  if ( fits_read_keys_lng(fptr, "NAXIS", 1, 2, naxes, &nfound, &status) )
  	printerror( status );

  npixels = naxes[0] * naxes[1];		/* number of pixels in the images */
  first_element = 1;
  nullval = 0.; 		    /* don't check for null values in the image */

  /* Allocate memory for array.  dmatrix return a pointer to the array, i.e.
   * the address of array[0][0].  ptr2ppix contains the address of the 
   * pointer to the array.  So *ptr2ppix contains the address of the array
   * Same as : ppix = dmatrix(naxes[1],naxes[0]);
   *           *ptr2ppix = ppix;
   */
  *ptr2ppix = dmatrix(naxes[1],naxes[0]);

  while (npixels > 0)
  {
    nbuffer = npixels;
    if (npixels > buffsize)
      nbuffer = buffsize;	   /* read as many pixels as will fit in buffer */

    if ( fits_read_img(fptr, TDOUBLE, first_element, nbuffer, &nullval,
    			buffer, &anynull, &status) )
	printerror( status );

    /* copy buffer to 2D array */
    for (i=0; i<nbuffer; i++) {
      if ((ii == naxes[0]) || (jj == naxes[1])) {  /* Outside allocated memomy */
        printf("Error: Segmentation fault (ppix)\n");
	 return(111);
      }
      *(*(*ptr2ppix + jj) + ii) = buffer[i];
      ii++;
      if (ii == naxes[0]) {	  /* if end of line, go to beginning of new line */
        ii=0;
	jj++;
      }
    }
    npixels -= nbuffer; 	/* increment remaining number of pixels */
    first_element  += nbuffer;	/* next pixel to be read in image */
  }

  printf("done\n");

  if ( fits_close_file(fptr, &status) )
  	printerror( status );
/*  free(fptr);  It seems to cause problems.  I don't know where I got
                 the idea to put it there but the new cookbook.c doesn't
		 have this line  (3 avril, 2001) */

  return(0);
}
