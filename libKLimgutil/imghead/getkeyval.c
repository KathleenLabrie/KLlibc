/* Main: getkeyval */
/* Version: 1.0.0 */
/*   Get the value associated with a given keyword
 *
 * Usage: getkeyval images|-l list -k keyword -d datatype
 *
 * Arguments:
 *      images: List of images;
 *      -l list:        File with list of images;
 *      -k keyword:     Specify the keyword to search for.
 *      -d datatype:    Datatype of the value.  (integer; see fitsio.h)
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
 int status;
 int nimages, n;
 char **pimages=NULL,**lines=NULL;
 char list[MAXLENGTH];
 char value[VALLENGTH], key[KEYLENGTH], comment[CMTLENGTH], dtype[MAXLENGTH];
 FILE *instream;

 status=0;
 strcpy(list,"");
 strcpy(value,"");
 strcpy(comment,"");

 /* Read command line */
 nimages = argc - 5;
 n=0;
 while (--argc > 0) {
   *++argv;
   if (!strncmp("-k",*argv,2)) {
     strcpy( key, *++argv );
     --argc;
   }
   else if (!strncmp("-l",*argv,2)) {
     strcpy( list, *++argv );
     --argc;
   }
   else if (!strncmp("-d",*argv,2)) {
     strcpy( dtype, *++argv );
     --argc;
   }
   else {
     if (n==0) {
      /* Create string vector */
       pimages = svector(nimages,MAXLENGTH);
     }
     strcpy( pimages[n++], *argv );
   }
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
   for (n=0; n<nimages; n++) {
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
   /* Read key */
   if (status = read_key(pimages[n], key, value, dtype, comment) )
   	printerror( status );

   /* Print value */
   printf("%s\n",value);
 }

 free_svector(pimages);
 exit(0);
}
