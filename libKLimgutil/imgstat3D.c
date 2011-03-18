/* Main : imgstat3D */
/* Version : 0.1.0 */
/*  Takes a list of images and calculate statistics for each pixel.  The
 *  stats use the values from the N images of *one given pixel*.  The results
 *  are output in an image, each output pixel containing the value of the
 *  statistical result.
 *
 *  Currently supports: average, standard deviation, standard error
 *
 * Usage: imgstat3D -l imlist -o output --stat=<statmode>
 *
 * Needs:
 *   %%%libKLimgutil%%%
 *   %%%libKLutil%%%
 *   %%%libKLfile%%%
 *   %%%libKLcfitsio%%%
 */

#include "./KLimgutil.h"
#include <KLutil.h>
#include <KLfile.h>
#include <KLcfitsio.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>	/* for NULL */
#include <string.h>	/* string operations */

/* statmode */
#define AVERAGE 1	
#define STDDEV 2	/* default */
#define STDERR 3

#define DEF_OUTPUT_NAME "statimg.fits"

#define NHEADERS 1

main (argc,argv)
int argc;
char *argv[];
{
 int status,i;
 long int nimages;
 unsigned long naxes[2], ii, jj;
 double avgsq;
 double **pimage=NULL, **psum=NULL, **psumsq=NULL, **presult=NULL;
 char **p_elem=NULL;
 char **images=NULL;
 char imgtitle[MAXLENGTH];
 KLFITS_HEADER *headers=NULL;
 
 unsigned int statmode;
 char imlist[MAXLENGTH], output[MAXLENGTH];
 
 status = 0;
 
 /* Defaults */
 statmode = STDDEV;
 strcpy(output,DEF_OUTPUT_NAME);
 
 /* Read command line */
 i=1;
 p_elem = svector(2,MAXLENGTH);
 while (i < argc) {
   if (!strncmp("--",argv[i],2)) {
     if (!strncmp("--stat",argv[i],6)) {
       splitstr( argv[i++], p_elem, "=" );
       if (!strncmp("av",p_elem[1],2)) statmode = AVERAGE;
       else if (!strncmp("stddev",p_elem[1],6)) statmode = STDDEV;
       else if (!strncmp("stderr",p_elem[1],6)) statmode = STDERR;
       else {
         fprintf(stderr,"ERROR: Unknown statistics (%s)\n",p_elem[1]);
	 exit(ERRNO_UNDEFINED_INPUT);
       } 
     }
     else {
       fprintf(stderr,ERRMSG_UNDEFINED_INPUT,argv[i]);
       exit(ERRNO_UNDEFINED_INPUT);
     }
   }
   else if (!strncmp("-",argv[i],1)) {
     if (!strncmp("-l",argv[i],2)) {
       strcpy( imlist, argv[++i] );
     }
     else if (!strncmp("-o",argv[i],2)) {
       strcpy( output, argv[++i] );
     }
     else {
       fprintf(stderr,ERRMSG_UNDEFINED_INPUT,argv[i]);
       exit(ERRNO_UNDEFINED_INPUT);
     }
     i++;
   }
   else {
     fprintf(stderr,ERRMSG_UNDEFINED_INPUT,argv[i]);
     exit(ERRNO_UNDEFINED_INPUT);
   }
 }
 free_svector(p_elem);
 if (strlen(imlist) == 0) {
   fprintf(stderr,"ERROR: No list of images specified.\n");
   exit(ERRNO_INPUT_ERROR);
 }
 
 /* Open image list and get the names */
 if ( status = rd_vec_string(imlist,NULL,NULL,1,&images,&nimages )) {
 	exit(status);
 }
 

 /* Loop through images calculating the stats 
  *   The calculation must be additive, keeping the current values in a
  *   2D array as large as the images. */
 for (i=0;i<nimages;i++) {
   if ( status = read_image(images[i],&pimage,naxes) ) {
   	if (images != NULL) free_svector(images);
	if (pimage != NULL) free_dmatrix(pimage);
	if (psum != NULL) free_dmatrix(psum);
	if (psumsq != NULL) free_dmatrix(psumsq);
	printerror( status );
   }
   if (psum == NULL) {
   	psum = dmatrixc(naxes[1],naxes[0]);
	psumsq = dmatrixc(naxes[1],naxes[0]);
   }
   
   
   switch (statmode)
   {
     case STDDEV:
     case STDERR:
     	for (jj=0;jj<naxes[1];jj++) 
	  for (ii=0;ii<naxes[0];ii++) {
	  	*(*(psumsq+jj)+ii) += DSQR( *(*(pimage+jj)+ii) );	
	  }
     case AVERAGE:
     	for (jj=0;jj<naxes[1];jj++)
	  for (ii=0;ii<naxes[0];ii++) *(*(psum+jj)+ii) += *(*(pimage+jj)+ii);
     	break;
     default:
     	fprintf(stderr,ERRMSG_INTERNAL_ERROR);
   	if (images != NULL) free_svector(images);
	if (pimage != NULL) free_dmatrix(pimage);
	if (psum != NULL) free_dmatrix(psum);
	if (psumsq != NULL) free_dmatrix(psumsq);	
	exit(ERRNO_INTERNAL_ERROR);
   }
   free_dmatrix(pimage);
   pimage=NULL;
 }

 /* Finish stat calculation */
 presult = dmatrix(naxes[1],naxes[0]);
 switch (statmode)
 {
   case AVERAGE:
   	for (jj=0;jj<naxes[1];jj++)
	  for (ii=0;ii<naxes[0];ii++) 
	  	*(*(presult+jj)+ii) = *(*(psum+jj)+ii) / nimages;
	sprintf(imgtitle,"Average of images in list %s",imlist);
   	break;
   case STDDEV:
   	for (jj=0;jj<naxes[1];jj++)
	  for (ii=0;ii<naxes[0];ii++) {
	  	avgsq = DSQR( *(*(psum+jj)+ii) / nimages );
	  	*(*(presult+jj)+ii) = (1./(nimages-1.)) * 
					(*(*(psumsq+jj)+ii) - nimages*avgsq);
		*(*(presult+jj)+ii) = sqrt( *(*(presult+jj)+ii) );
	  }
	sprintf(imgtitle,"Standard deviation of images in list %s",imlist);
   	break;
   case STDERR:
   	for (jj=0;jj<naxes[1];jj++)
	  for (ii=0;ii<naxes[0];ii++) {
	  	avgsq = DSQR( *(*(psum+jj)+ii) / nimages );
	  	*(*(presult+jj)+ii) = (1/(nimages-1)) * 
					(*(*(psumsq+jj)+ii) - nimages*avgsq);
		*(*(presult+jj)+ii) = sqrt( *(*(presult+jj)+ii) / nimages );
	  }
	sprintf(imgtitle,"Standard error of images in list %s",imlist);
   	break;
   default:
   	fprintf(stderr,ERRMSG_INTERNAL_ERROR);
   	if (images != NULL) free_svector(images);
	if (psum != NULL) free_dmatrix(psum);
	if (psumsq != NULL) free_dmatrix(psumsq);
	if (presult != NULL) free_dmatrix(presult);
	exit(ERRNO_INTERNAL_ERROR);
 }
 /* Free some memory */
 free_svector(images);
 free_dmatrix(psum);
 free_dmatrix(psumsq);
 
 /* Create header for result image */
 headers = klfits_header_vector(NHEADERS);
 strcpy(headers[0].keyword,"title");
 strcpy(headers[0].value_str, imgtitle);
 headers[0].datatype = TSTRING;
 
 /* Create result image */
 if (status = create_image( output, presult, naxes, headers, NHEADERS )) {
 	if (presult != NULL) free_dmatrix(presult);
	printerror( status );
 }

 exit(0);
}
