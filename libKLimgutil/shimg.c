/* Main : shimg */
/* Version: 1.1.0 */
/* Shift a FITS image
 *
 * Command-line args: fname (-o newfname) dx dy --log=logfile
 *
 *	fname		: Name of the input image.
 *	-o newfname	: Name of the output image. (optional, default overwrites)
 *	dx		: Horizontal shift to apply	( shift[0] )
 *	dy		: Vertical shift to apply	( shift[1] )
 *	--log=logfile	: Specify a log file (default: none)
 *
 * Needs
 *   %%%libKLimgutil%%%
 *   %%%libKLcifitsio%%%
 *   %%%libKLutil%%%
 */

#include "./KLimgutil.h"
#include <KLutil.h>
#include <KLcfitsio.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

main(argc,argv)
int argc;
char *argv[];
{
 char fname[MAXLENGTH], newfname[MAXLENGTH];
 int status,i,dim;
 long shift[2];
 unsigned long naxes[2];
 double **array=NULL;
 char logfile[MAXLENGTH],**p_elem, message[MAXLENGTH],tmp[MAXLENGTH];
 char keyword[MAXLENGTH], comment[MAXLENGTH], *pname;
 struct tm the_time;
 char the_month[4];
 time_t now;

 status = 0;
 p_elem = svector(2,MAXLENGTH);

/* Read inputs */
 i=1;
 dim=0;
 while (i < argc) {
   if (!strncmp("-o",argv[i],2)) {
     strcpy( newfname, argv[++i] );
     i++;
   }
   else if (!strncmp("--log",argv[i],5)) {
     splitstr( argv[i++], p_elem, "=");
     strcpy(logfile,p_elem[1]);
   }
   else {
     if (!strlen(fname)) {
       strcpy(fname,argv[i++]);
     }
     else {
       shift[dim++]=atoi(argv[i++]);
     }
   }
 }

free_svector(p_elem);
 if (dim != 2) {
 	printf ("'Dim' not equal to 2.\n");
	exit(1);
 }

 if (!strlen(newfname)) { strcpy(newfname,fname); }
 
 printf("Shifting image %s -> %s  (%d, %d) ... ",fname,newfname,shift[0],
 	shift[1]);

 if ( status = read_image(fname, &array, naxes) ) {
 	if (array != NULL) free_dmatrix(array);
 	printerror( status );
 }
 if ( status = shift_image(array, naxes, shift[0], shift[1]) ) {
 	free_dmatrix(array);
 	printerror( status );
 }
 if ( status = edit_image(fname, newfname, array) ) {
 	free_dmatrix(array);
 	printerror( status );
 }

 /* Edit header (SHIFT#  tags) */
 time(&now);
 the_time = *localtime( &now );
 month(the_time.tm_mon, the_month);
 pname = strrchr(fname,'/') + 1;
 sprintf(message,"%s %d %d:%02d Shifted by (%d, %d) from %s", 
 		the_month,
		the_time.tm_mday,
		the_time.tm_hour,
		the_time.tm_min,
		shift[0], shift[1],
		pname);
 strcpy(keyword, "SHIFT");
 strcpy(comment,"");
 if ( status = write_numbered_key(newfname, keyword, message, "string", comment)) {
 	if (strlen(logfile)) {
	  sprintf(message, "%s: ERROR: Unable to update header.\n", fname);
	  wrlog(logfile,message);
	}
	printerror( status );
 } else {
 	if (strlen(logfile)) {
  	  strcpy(tmp,fname);
	  strcat(tmp,": ");
	  strcat(tmp, message);
	  strcpy(message, tmp);
	  strcat(message, "\n");
	  if ( status = wrlog(logfile,message) ) {
     		free_dmatrix(array);
     		printf("%s : ",logfile);
     		printerror(status);
	  }
	}
 }

 printf("done\n");

 free_dmatrix(array);

 exit(0);
}

