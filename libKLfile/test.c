/* test */

#include "./KLfile.h"
#include <stdio.h>
#include <stdlib.h> /* for gcc4.0, exit */
#include <string.h>

#define MAXLENGTH 80
#define INPUT_FILE "testfile.dat"

main( argc, argv )
int argc;
char *argv[];
{
 int status=0;
 long int i,nlines;
 double *c1=NULL, *c2=NULL;
 FILE *instream;
  
 status = rd_set_double(INPUT_FILE,&c1,&c2,&nlines);

 for (i=0;i<nlines;i++) { printf("%d %f %f\n",i,*(c1+i),*(c2+i)); }

 exit(0);
}
