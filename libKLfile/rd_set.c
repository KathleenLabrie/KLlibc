/* Function : rd_set */
/* Version: 0.1.0 
 *   Functions to read the first two columns of a file
 *
 * int rd_set_int(char filename[], > int **col1, > int **col2, > int *n)
 * int rd_set_long_int(char filename[], > long int **col1, > long int **col2, > int *n)
 * int rd_set_float(char filename[], > float **col1, > float **col2, > int *n)
 * int rd_set_double(char filename[], > double **col1, > double **col2,>  int *n)
 *
 * Arguments:
 *   Inputs :
 *		file name			- char filename[]
 *   Outputs :
 *		address of column vectors 	- <type> **col1, **col2
 *		length of vectors		- int *n
 *
 * Output:
 *   Status code (0 for success).
 *
 * Calling rd_set_<type>
 *   #include <KLfile.h>
 *   ...
 *   <type> *col1=NULL, *col2=NULL;
 *   status = rd_set_<type>(filename, &col1, &col2, &n);
 *
 * Needs :
 *   %%%libKLutil%%%
 *
 */

#include "./KLfile.h"
#include <KLutil.h>
#include <stdio.h>
#include <stdlib.h>	/* for  atof() */

int rd_set_double(char filename[], double **ptr2col1, double **ptr2col2, 
		long int *n)
{
 int status=0;
 long int i;
 char line[MAXLENGTH],**p_line;
 FILE *istream;

 /* open file */
 if ( (istream = fopen(filename,"r")) == NULL) {
   fprintf(stderr,ERRMSG_FILE_NOT_FOUND,filename);
   return(ERRNO_FILE_NOT_FOUND);
 }

 /* find number of lines */
 *n=0;
 while (fgets( line, MAXLENGTH, istream ) != NULL) { (*n)++; }
 rewind(istream); 
 
 /* allocate memory for col1 and col2 */
 *ptr2col1 = dvector(*n);
 *ptr2col2 = dvector(*n);
 
 /* read file */
 p_line = svector(MAXCOLS, MAXLENGTH);
 for (i=0;i<*n;i++) {
   if ( fgets( line, MAXLENGTH, istream ) == NULL ) {
     status = ERRNO_IO_ERROR;
     break;
   }
   splitstr( line, p_line, SPACES );
   *(*ptr2col1+i) = atof( p_line[0] );
   *(*ptr2col2+i) = atof( p_line[1] );
 }
 free_svector(p_line);
 
 /* close file */
 fclose(istream);
 istream=NULL;

 return(status);
}
