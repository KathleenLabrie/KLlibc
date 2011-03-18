/* Function: wrcube */
/* Version: 0.1.1 */
/*   Write cube to file or stdout.
 *
 * int wrcube(char filename[], FILE *ostream, fpos_t *pos, 
 *		double ***cube, double *axis1, double *axis2, double *axis2,
 *            	long int n1,long int n2,long int n3);
 *
 */

#include <KLutil.h>
#include <stdio.h>
#include <stddef.h>	/* for NULL */
#include <string.h>	/* for strncmp */

int wrcube(char filename[], FILE *ostream, fpos_t *pos, double ***cube, 
		double *axis1, double *axis2, double *axis3,
		long int n1,long int n2,long int n3)
{
 long int i,j,k,status=0;
 FILE *the_stream;
 fpos_t the_pos;
 
 /* open new file if not done already */
 if ( ostream == NULL ) {
   if ( (the_stream = fopen(filename,"w")) == NULL) {
   	fprintf(stderr,ERRMSG_IO_ERROR,filename);
	return(ERRNO_IO_ERROR);
   }
   fgetpos(the_stream,&the_pos);
 } else {
   the_stream = ostream;
   the_pos = *pos;
 }

 

 /* Move the file position indicator */
 if ( status = fsetpos(the_stream,&the_pos) ) {
 	fprintf(stderr,ERRMSG_IO_ERROR,filename);
	return(ERRNO_IO_ERROR);
 }
 
 fprintf(the_stream,"%d  %d  %d\n",n1,n2,n3);
 for (i=0;i<n1;i++) {
    fprintf(the_stream,"%.2g  ",*(axis1+i));
 }
 fprintf(the_stream,"\n");
 for (i=0;i<n2;i++) {
    fprintf(the_stream,"%.2g  ",*(axis2+i));
 }
 fprintf(the_stream,"\n");
 for (i=0;i<n3;i++) {
    fprintf(the_stream,"%.2g  ",*(axis3+i));
 }
 fprintf(the_stream,"\n");
 for (k=0;k<n3;k++) {
   for (j=0;j<n2;j++) {
     for (i=0;i<n1;i++) {
       fprintf(the_stream,"%g  ",*(*(*(cube+k)+j)+i));
     }
     fprintf(the_stream,"\n");
   }
 }

 /* close file, if ostream NULL */
 if (ostream == NULL) {
    fclose(the_stream);
    the_stream=NULL;
 } else {
    fgetpos(the_stream,&the_pos);
    *pos = the_pos;
 }

 return(status);
}
