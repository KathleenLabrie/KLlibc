/* Main : tail2head */
/* Version: 0.1.1 */
/*   Reverse the lines in a file such that the tail line becomes the head line
 *   and vice versa.
 *
 *   Overwrites the file
 *
 * Usage: tail2head [-vh] file
 *
 *	file	: File name
 *	-h	: Print help
 *	-v	: Toggle on verbose
 *
 * Needs:
 *   %%%libKLutil%%%
 */

#include <KLutil.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* for gcc4.0, exit */

#define HELP_TAIL2HEAD \
"\nUsage: tail2head [-vh] file\n\
  file	: File name\n\
  -h	: Print this help\n\
  -v	: Toggle on verbose\n"

main(argc,argv)
int argc;
char *argv[];
{
 int i,n,status=0;
 int FLAGS;
 char **lines, line[MAXLENGTH];
 char filename[MAXLENGTH];
 FILE *istream;

 /* Initialize */
 FLAGS=0;

 /* Read command line */
 i=1;
 while (i < argc) {
   if (!strncmp("-h",argv[i],2)) { printf("%s",HELP_TAIL2HEAD); exit(0); }
   else if (!strncmp("-v",argv[i],2)) { FLAGS |= 1 << VERBOSE; }
   else {
     strcpy(filename,argv[1]);
   }
   i++;
 }
 
 /* Open file for reading */
 if ( (istream = fopen(filename,"r")) == NULL ) {
   fprintf(stderr,ERRMSG_FILE_NOT_FOUND,filename);
   exit(ERRNO_FILE_NOT_FOUND);
 }

 /* Count number of lines */ 
 n=0;
 while ( fgets(line, MAXLENGTH, istream) != NULL ) { n++; }
 rewind(istream);
 
 /* Allocate memory for lines */
 lines = svector(n,MAXLENGTH);
 
 /* Read file */
 for (i=0;i<n;i++) { fgets(lines[i], MAXLENGTH, istream); }
 
 /* Close file and reopen for writing */
 fclose(istream);
 istream=NULL;
 if ( (istream = fopen(filename,"w")) == NULL ) {
   fprintf(stderr,ERRMSG_IO_ERROR,filename);
   exit(ERRNO_IO_ERROR);
 }
 
 /* Write lines from tail to head */
 for (i=n-1;i>=0;i--) { fprintf(istream,"%s",lines[i]); }
 
 /* Close file and exit */
 fclose(istream);
 istream=NULL;
 
 exit(0);
}
 
