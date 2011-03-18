/* Main: maskout */
/* Version: 1.0.1 */
/*	Replace the value of the pixels listed by another value.
 *	e.g. Set all pixels in a mask to zero.
 *
 * Usage: maskout image mask -o output --offset=dx,dy --value=z --log=logfile
 *		--clobber
 *
 *	image			: Name of the input image.
 *	mask			: Name of the pixel list.
 *	-o output		: Name of the output image (Default overwrites).
 *	--offset=dx,dy	: Offset to apply to the mask.
 *	--value=z		: New value (Default is zero).
 *	--log=logfile		: Specify a log file (Default: none).
 *	--clobber		: Won't print any warning concerning overwrites.
 *
 * Needs
 *   %%%libKLimgutil%%%
 *   %%%libKLutil%%%
 *   %%%libKLcfitsio%%%
 */

#include "./KLimgutil.h"
#include <KLutil.h>
#include <KLcfitsio.h>
#include <stdio.h>		/* for sprintf */
#include <stddef.h>		/* for NULL */
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEFAULT_VALUE 0
#define DEFAULT_XOFFSET 0
#define DEFAULT_YOFFSET 0
#define CLOBBER 0		/* don't overwrite without user confirmation */

main(argc,argv)
int argc;
char *argv[];
{
 char image[MAXLENGTH], newimage[MAXLENGTH], mask[MAXLENGTH];
 int status,i,clobber;
 long offset[2], ii, jj;
 unsigned long naxes[2],n;
 double **ppix=NULL, value,**pcoo=NULL;
 char logfile[MAXLENGTH],**p_elem, message[2*MAXLENGTH], tmp[2*MAXLENGTH];
 char keyword[MAXLENGTH], comment[MAXLENGTH], answer, *shortmask;
 struct tm the_time;
 char the_month[4];
 time_t now;

 /* Initialize */
 value = DEFAULT_VALUE;
 offset[0] = DEFAULT_XOFFSET;
 offset[1] = DEFAULT_YOFFSET;
 strcpy(logfile,"");
 strcpy(newimage,"");
 clobber=CLOBBER;
 status=0;

 /* Read command line */
 strcpy(image,argv[1]);
 strcpy(mask,argv[2]);
 i=3;
 p_elem = svector(2,MAXLENGTH);
 while (i < argc) {
   if (!strncmp("-o",argv[i],2)) {
     strcpy( newimage, argv[++i] );
     i++;
   }
   else if (!strncmp("--clobber",argv[i],9)) {
     n=splitstr( argv[i++], p_elem, "=");
     if (n==1) { clobber=1; }
     else { clobber=atoi(p_elem[1]); }
   }
   else if (!strncmp("--log",argv[i],5)) {
     splitstr( argv[i++], p_elem, "=");
     strcpy(logfile,p_elem[1]);
   }
   else if (!strncmp("--offset",argv[i],8)) {
     splitstr( argv[i++], p_elem, "=");
     strcpy(tmp,p_elem[1]);
     splitstr( tmp, p_elem, ",");
     offset[0] = atoi(p_elem[0]);
     offset[1] = atoi(p_elem[1]);
   }
   else if (!strncmp("--value",argv[i],7)) {
     splitstr( argv[i++], p_elem, "=");
     value = atof(p_elem[1]);
   }
   else {
     printf("ERROR: Unknown switch (%s)\n",argv[i]);
     exit(1);
   }
 }
 free_svector(p_elem);

 if (!strlen(newimage)) {
    if (!clobber) {
      printf("WARNING: Will overwrite %s.  Confirm? (y/n)\n",image);
      scanf("%c",&answer);
      if ((answer != 89) && (answer != 121)) {	/* not 'y' or 'Y' */
        printf("Specify an output file name with -o\n");
	 printf("Now exiting...\n");
	 exit(1);
      }
    }
    strcpy(newimage,image);
 }
 
 printf("Masking image %s with value %f -> %s ... ",image,value,newimage);

 /* Read image */
 if ( status = read_image(image, &ppix, naxes) ) {
 	if (ppix != NULL) free_dmatrix(ppix);
	printerror( status );
 }
 /* Read list of pixels */
 if ( status = read_points(mask, &pcoo, &n, offset[0], offset[1]) ) {
 	if (pcoo != NULL) free_dmatrix(pcoo);
	free_dmatrix(ppix);
	printf("\nERROR: Unable to read mask file.\n");
	exit(1);
 }

 /* Replace */
 for (i=0;i<n;i++) {
   ii = (int)pcoo[i][0];	/* -1 done in read_points */
   jj = (int)pcoo[i][1];
   if ((ii>=0) && (ii<naxes[0]) && (jj>=0) && (jj<naxes[1])) {
     *(*(ppix+ jj) + ii) = value;
   }
 }
 free_dmatrix(pcoo);

 /* Write new image */
 if ( status = edit_image(image, newimage, ppix) ) {
 	free_dmatrix(ppix);
	printerror(status);
 }
 free_dmatrix(ppix);
 
 /* Edit header (MASKED keyword) */
 time(&now);
 the_time = *localtime( &now );
 month(the_time.tm_mon, the_month);
 shortmask = strrchr(mask,'/') + 1;
 if (shortmask == NULL+1) { shortmask = mask; }
 sprintf( message, "%s %d %d:%02d Pixels replace by %.2f (%s [%d,%d])",
 		the_month,
		the_time.tm_mday,
		the_time.tm_hour,
		the_time.tm_min,
		value, shortmask, offset[0], offset[1]);
 strcpy(keyword, "MASKED");
 strcpy(comment,"");
 if ( status = write_key(newimage, keyword, message, "string", comment) ) {
 	if (strlen(logfile)) {
	  sprintf(message, "%s: ERROR: Unable to update header.\n", image);
	  wrlog(logfile,message);
	}
	printerror( status );
 } else {
 	if (strlen(logfile)) {
	  strcpy(tmp,image);
	  strcat(tmp,": ");
	  strcat(tmp, message);
	  strcpy(message, tmp);
	  strcat(message, "\n");
	  if (status = wrlog(logfile,message) ) {
	  	printf("%s : ",logfile);
		printerror(status);
	  }
	}
 }

 printf ("done\n");
 
 exit(0);
}
