/*test*/

#include "./KLinter.h"
#include <KLutil.h>
#include <KLfile.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

main(argc,argv)
int argc;
char *argv[];
{
 int status;
 long int n,k;
 int degree;
 unsigned long guess;
 double value,inter,err;
 double *x=NULL,*y=NULL;
 char file[MAXLENGTH];

 strcpy(file,argv[1]);

 value = atof(argv[2]);
 degree = atoi(argv[3]);
 guess = atoi(argv[4]);

 if ( status = rd_set_double(file,&x,&y,&n) ) {
   if (x != NULL) {free_dvector(x);}
   if (y != NULL) {free_dvector(y);}
   fprintf(stderr,ERRMSG_IO_ERROR);
   exit(status);
 }
  
 dhunt(x,n,value,&guess);
 k=IMIN(IMAX(guess-(degree-1)/2,0),n-(long int)degree);
 
 printf("center=%d\nx[%d]=%f\n",guess,k,x[k]);
 
 dpolint(&x[k],&y[k],degree,value,&inter,&err);
 printf("at %f -> inter=%f, err=%f\n",value,inter,err);

 exit(0);
}
