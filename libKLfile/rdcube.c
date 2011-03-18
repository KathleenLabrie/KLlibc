/* Function : rdcube */
/* Version : 0.1.0 */
/*   Read cube from a file.
 *
 * int rdcube(char filename[], FILE *istream, fpos_t *pos, 
 *		double ****pcube, double **paxis1, double **paxis2,
 *		double **paxis3, long int *n1, long int *n2, long int *n3);
 */

#include <KLutil.h>
#include <stdio.h>
#include <stddef.h>	/* for NULL */

int rdcube(char filename[], FILE *istream, fpos_t *pos, 
 		double ****pcube, double **paxis1, double **paxis2,
		double **paxis3, long int *n1, long int *n2, long int *n3)
{
 int status=0;
 long int i,j,k;
 double *axis=NULL,value;
 char line[MAXLENGTH];
 FILE *the_stream;
 fpos_t the_pos;
 
 /* open new file if not done already */
 if ( istream == NULL ) {
    if ( (the_stream = fopen(filename,"r")) == NULL) {
    	fprintf(stderr,ERRMSG_IO_ERROR,filename);
	return(ERRNO_IO_ERROR);
    }
    fgetpos(the_stream,&the_pos);
 } else {
    the_stream = istream;
    the_pos = *pos;
 }
 
 /* Move the file position indicator */
 if ( status = fsetpos(the_stream,&the_pos) ) {
 	fprintf(stderr,ERRMSG_IO_ERROR,filename);
	return(ERRNO_IO_ERROR);
 }
 

 fscanf(the_stream,"%d  %d  %d\n",n1,n2,n3);

 /* allocate memory when required */
 if (*pcube == NULL) { *pcube=dcube(*n3,*n2,*n1); }
 if (*paxis1 == NULL) { *paxis1=dvector(*n1); }
 if (*paxis2 == NULL) { *paxis2=dvector(*n2); }
 if (*paxis3 == NULL) { *paxis3=dvector(*n3); }

 for (i=0;i<*n1;i++)  fscanf(the_stream,"%lg  ",(*paxis1+i));
 fscanf(the_stream,"\n");
 for (j=0;j<*n2;j++)  fscanf(the_stream,"%lg  ",(*paxis2+j));
 fscanf(the_stream,"\n");
 for (k=0;k<*n3;k++)  fscanf(the_stream,"%lg  ",(*paxis3+k));
 fscanf(the_stream,"\n");
 for (k=0;k<*n3;k++) {
   for (j=0;j<*n2;j++) {
     for (i=0;i<*n1;i++) fscanf(the_stream,"%lg  ",(*(*(*pcube+k)+j)+i));
     fscanf(the_stream,"\n");
   }
 }

 /* close file, if istream NULL */
 if (istream == NULL) {
    fclose(the_stream);
    the_stream=NULL;
 } else {
    fgetpos(the_stream,&the_pos);
    *pos = the_pos;
 }

 return(status);
}
