/* Main: dellines */
/* Version: 1.0.0 */
/*	Delete a set of rows or columns from a FITS image.
 *
 * Usage: dellines -r|-c -o prefix --log=logfile images|-l list mmm nnn
 *
 *	-r:		Delete rows
 *	-c:		Delete columns
 *	-o prefix:	Prefix given to output images [default: overwrite]
 *	--log=logfile	Name of the log file
 *	images:		Input images
 *	-l list:	File with list of input images
 *	mmm:		From row/column number mmm
 *	nnn:		To row/column number nnn
 *
 * Needs:
 *   %%%libKLcfitsio%%%
 *   %%%libKLimgutil%%%
 *   %%%libKLutil%%%
 */

#include "./KLimgutil.h"
#include <KLcfitsio.h>
#include <KLutil.h>
#include <stdio.h>		/* for file I/O */
#include <stddef.h>		/* for NULL */
#include <stdlib.h>		/* for atoi */
#include <time.h>		/* for time, localtime, struct tm */

#define COLUMN 1
#define ROW 0
#define MAXNCOL MAXLENGTH

main( argc, argv )
int argc;
char *argv[];
{
 int status=0, mode=-1;
 int i, j, k, ii, jj, kk, ll, nimages;
 unsigned long limit1, limit2, naxes[2];
 double **ppix=NULL, **pnew=NULL;
 char **ptmp=NULL, **pimages=NULL;
 char input[MAXLENGTH], prefix[MAXLENGTH/2], output[MAXLENGTH];
 char logfile[MAXLENGTH], imlist[MAXLENGTH];
 char message[3*MAXLENGTH], keyword[MAXLENGTH], comment[MAXLENGTH];
 char line[MAXLENGTH], **p_lines, **p_parse, tmp[MAXLENGTH];
 struct tm the_time;
 char the_month[4];
 time_t now;
 FILE *flist;

 /* Initialize */
 strcpy(prefix,"");
 strcpy(logfile,"");
 strcpy(imlist,"");
 ptmp = svector(argc-4,MAXLENGTH);

 /* Read command line */
 i=1;
 j=0;
 while (i < argc-2) {
   if (!strncmp("-c",argv[i],2)) {
     mode=COLUMN;
   }
   else if (!strncmp("-l",argv[i],2)) {
     strcpy( imlist, argv[++i] );
   }
   else if (!strncmp("-o",argv[i],2)) {
     strcpy( prefix, argv[++i] );
   }
   else if (!strncmp("-r",argv[i],2)) {
     mode=ROW;
   }
   else if (!strncmp("--log",argv[i],5)) {
     p_parse = svector(2,MAXLENGTH);
     splitstr(argv[i], p_parse, "=");
     strcpy( logfile, p_parse[1] );
     free_svector(p_parse);
   }
   else {
     strcpy(ptmp[j++], argv[i]);
   }
   i++;
 }
 limit1 = atoi(argv[argc-2]);
 limit2 = atoi(argv[argc-1]);

 /* Make sure a mode has been specified */
 if ( mode == -1 ) {
   printf("ERROR: Specify whether to use rows (-r) or columns (-c)\n");
   exit(1);
 }

 /* Read image list, if specified */
 if (strlen(imlist) != 0) {
   /* Get the number of images.  Double access but no limit on nimages. */
   k=0;
   if (( flist = fopen( imlist, "r" ) ) == NULL) {
        free_svector(ptmp);
   	printerror(FILE_NOT_OPENED);
   }
   while (fgets( line, MAXLENGTH, flist) != NULL) {
     k++;
   }
   fclose(flist);
   nimages = k + j;
   pimages = svector(nimages,MAXLENGTH);
   for (i=0; i<j; i++) {
     strcpy(pimages[i], ptmp[i]);
   }
   free_svector(ptmp);
   if (( flist = fopen( imlist, "r" ) ) == NULL) {
   	printerror(FILE_NOT_OPENED);
   }
   p_lines = svector(MAXNCOL, MAXLENGTH);
   while (fgets( line, MAXLENGTH, flist) != NULL) {
     splitstr(line, p_lines, SPACES);
     strcpy(pimages[i++],p_lines[0]);
   }
   free_svector(p_lines);
 }
 else {
   nimages = j;
   pimages = svector(nimages,MAXLENGTH);
   for (j=0; j<nimages; j++) {
     strcpy(pimages[j], ptmp[j]);
   }
   free_svector(ptmp);
 }

 if (nimages <= 0) {
   printf("ERROR: No input files\n");
   exit(1);
 }

 /*** Start looping over images ***/
 for (i=0; i<nimages; i++) {
   /* Read image */
   if ( status = read_image( pimages[i], &ppix, naxes ) ) {
   	if (ppix != NULL) { free_dmatrix(ppix); }
	free_svector(pimages);
	if (strlen(logfile)) {
	  sprintf(message, "%s: ERROR: Unable to read image.\n", pimages[i]);
	  wrlog(logfile, message);
	}
	printerror( status );
   }

   /* Delete lines */
   pnew = dmatrix(naxes[1],naxes[0]);
   switch (mode) {
     case ROW:
     		for (jj=0,ll=0; jj<naxes[1]; jj++,ll++) {
		  for (ii=0,kk=0; ii<naxes[0]; ii++,kk++) {
		    if ( (jj<limit1) || (jj>limit2) ) {		/* good row */
			*(*(pnew+ll)+kk) = *(*(ppix+jj)+ii);
		    }
		    else {					/* bad row */
			ii=naxes[0];	/* go to next row */
			ll--;		/* cancel new image row increment */
		    }
		  }
		}
		break;
     case COLUMN:
     		for (ii=0,kk=0; ii<naxes[0]; ii++,kk++) {
		  for (jj=0,ll=0; jj<naxes[1]; jj++,ll++) {
		    if ( (ii<limit1) || (ii>limit2) ) {		/* good column */
		    	*(*(pnew+ll)+kk) = *(*(ppix+jj)+ii);
		    }
		    else {					/* bad column */
		    	jj=naxes[1];	/* go to next column */
			kk--;		/* cancel new image column increment */
		    }
		  }
		}
		break;
     default:
     		sprintf(message, "%s: ERROR: Invalid mode.\n", pimages[i]);
		printf("%s",message);
		if (strlen(logfile)) {
		  wrlog(logfile, message);
		}
		exit(1);
   }	/* end switch */
 
   /* Write new image */
   strcpy(output,prefix);
   strcat(output,pimages[i]);
   if ( status = edit_image( pimages[i], output, pnew ) ) {
   	free_dmatrix(ppix);
	free_dmatrix(pnew);
	free_svector(pimages);
	if (strlen(logfile)) {
	  sprintf(message, "%s: ERROR: Unable to write corrected image.\n", pimages[i]);
	  wrlog(logfile, message);
	}
	printerror( status );
   }

   /* Edit header (MOD# tag) */
   time(&now);
   the_time = *localtime( &now );
   month(the_time.tm_mon, the_month);
   sprintf(message,"%s %d %d:%02d %s %d to %d removed",
   		the_month,
		the_time.tm_mday,
		the_time.tm_hour,
		the_time.tm_min,
		(mode==0) ? "Rows" : "Columns",
		limit1,
		limit2);
   strcpy(keyword, "MOD");
   strcpy(comment,"");
   if ( status = write_numbered_key(output, keyword, message, "string", comment) ) {
   	if (strlen(logfile)) {
	  sprintf(message, "%s: ERROR: Unable to update header.\n", pimages[i]);
	  wrlog(logfile, message);
	}
	printerror( status );
   } else {
   	if (strlen(logfile)) {
	  strcpy(tmp,pimages[i]);
	  strcat(tmp,": ");
	  strcat(tmp, message);
	  strcpy(message, tmp);
	  wrlog(logfile, message);
	}
   }

   /* Desallocate memory */
   free_dmatrix(ppix);
   free_dmatrix(pnew);
 }	/* end loop over images */

 /* Desallocate memory */
 free_svector(pimages);

 exit(0);
}
