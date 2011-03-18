/* Main: chkey */
/* Version: 1.0.0 */
/*   Change the name of a keyword in a FITS file header
 *
 * Usage: chkey images|-l list -o old_key -n new_key 
 *
 * Arguments:
 *	images:  List of images;
 *	-l list: File with list of images;
 *	old_key: Keyword that needs to be changed (must exist);
 *	new_key: New name for the keyword;
 *
 * Needs:
 *   %%%libKLcfitsio%%%
 *   %%%libKLutil%%%
 */

#include "./KLimghead.h"
#include <KLutil.h>
#include <KLcfitsio.h>
#include <stdio.h>
#include <string.h>

main(argc,argv)
int argc;
char *argv[];
{
 char old_key[KEYLENGTH],new_key[KEYLENGTH];
 char **pimages,**lines;
 char list[MAXLENGTH];
 int nimages,n;
 int status;
 FILE *instream;

 if (argc < 6) {
   printf("Usage: chkey images|-l list -o old_key -n new_key\n");
   exit(1);
 }
 
 /* Read in command-line arguments */
 nimages=argc-5;
 n=0;
 while (--argc > 0) {
   *++argv;
   if (!strncmp("-o",*argv,2)) {
     strcpy( old_key, *++argv );
     --argc;
   }
   else if (!strncmp("-n",*argv,2)) {
     strcpy( new_key, *++argv );
     --argc;
   }
   else if (!strncmp("-l",*argv,2)) {
     strcpy( list, *++argv );
     --argc;
   }
   else { 
     if (n==0) pimages = svector(nimages,MAXLENGTH);
     strcpy( pimages[n++], *argv );}
 }

 if (strcmp(list,"")) {
   instream = fopen(list,"r");
   lines = svector(MAXFILES,MAXLENGTH);
   n=0;
   while (!feof(instream)) {
     fscanf(instream,"%s\n",lines[n++]);
   }
   fclose(instream);
   clearerr(instream);
   /* Create string vector */
   nimages = n;
   pimages = svector(nimages,MAXLENGTH);
   for (n=0;n<nimages;n++) {
     strcpy(pimages[n],lines[n]);
   }
   free_svector(lines);
}

 /* Check number of images */
 if (n != nimages) {
   printf ("ERROR: Error reading image names.\n");
   free_svector(pimages);
   exit(1);
 }

 for (n=0; n<nimages; n++) {
   /* Modify keyword */
   if ( status = modify_key(pimages[n], old_key, new_key ) ) {
	if (status == 202) { status=0; }
	else { 
	  free_svector(pimages);
	  printerror( status );
	}
   }
 }

 free_svector(pimages);
 exit(0);
}

