/* Function : rd_vec */
/* Version: 0.1.0
 *
 * int rd_vec_string(char filename[], FILE *istream, int colno, 
 *						>char ***ptr2vec, > *n)
 * int rd_vec_double(char filename[], FILE *istream, int colno, 
 *						> double **ptr2vec, > *n)
 *
 * Arguments:
 *
 *
 * Output:
 *   Status code (0 for success).
 *
 * Calling rd_vec_<type>
 *   #include <KLfile.h>
 *   ...
 *   <type> *vec=NULL;  or char **vec=NULL;
 *   
 *   status = rd_vec_<type>(filename,NULL,colno,&vec,&n);
 *   status = rd_vec_<type>(filename,istream,colno,&vec,&n);
 *
 * Needs :
 *   %%%libKLutil%%%
 *
 */

#include "./KLfile.h"
#include <KLutil.h>
#include <stdio.h>
#include <stdlib.h>	/* for atof() */
#include <string.h>	/* for strcpy() */
#include <stddef.h>	/* for NULL */

int rd_vec_string(char filename[], FILE *istream, fpos_t *fpos,
		long int colno, char ***ptr2vec, long int *n)
{
 int i,nitem,status=0;
 char line[2*MAXLENGTH],**parse_line;
 FILE *the_stream=NULL;
 fpos_t the_pos;

 /* open file if not done already */
 if ( istream == NULL ) {
    if ( (the_stream = fopen(filename,"r")) == NULL) {
   	fprintf(stderr,ERRMSG_FILE_NOT_FOUND,filename);
	return(ERRNO_FILE_NOT_FOUND);
    }
    fgetpos(the_stream,&the_pos);
 } else {
    the_stream = istream;
    the_pos = *fpos;
 }
 
 /* Move the file position indicator */
 if ( status = fsetpos(the_stream,&the_pos) ) {
 	fprintf(stderr,ERRMSG_IO_ERROR,filename);
 	return(ERRNO_IO_ERROR);
 }
 
 /* find number of lines */
 i=0;
 while (fgets( line, 2*MAXLENGTH, the_stream ) != NULL) { i++; }
 if (*ptr2vec != NULL ) { nitem = (i<=*n) ? i : *n; }
 else                   { nitem = i; *n=nitem;      }
 /* rewind */
 fsetpos(the_stream,&the_pos);

 /* allocate memory for vector */
 if (*ptr2vec == NULL ) { *ptr2vec = svector(nitem,MAXLENGTH); }
 
 /* read file */
 parse_line = svector(MAXCOLS,MAXLENGTH);
 for (i=0; i<nitem; i++) {
   if ( fgets( line, 2*MAXLENGTH, the_stream ) == NULL ) {
   	fprintf(stderr,ERRMSG_IO_ERROR,filename);
	break;
   }
   splitstr( line, parse_line, SPACES );
   strcpy( *(*ptr2vec+i), parse_line[colno-1] );
 }
 free_svector(parse_line);
 
 /* close file, if istream NULL */
 if (istream == NULL) { 
    fclose(the_stream);
    the_stream=NULL;
 } else {
    fgetpos(the_stream,&the_pos);
    *fpos = the_pos;
 }
 
 return(status);
}

/* **************** */

int rd_vec_double(char filename[], FILE *istream, fpos_t *fpos, 
		long int colno, double **ptr2vec, long int *n)
{
 int i,nitem,status=0;
 char line[2*MAXLENGTH],**parse_line;
 FILE *the_stream=NULL;
 fpos_t the_pos;

 /* open file if not done already */
 if ( istream == NULL ) {
    if ( (the_stream = fopen(filename,"r")) == NULL) {
   	fprintf(stderr,ERRMSG_FILE_NOT_FOUND,filename);
	return(ERRNO_FILE_NOT_FOUND);
    }
    fgetpos(the_stream,&the_pos);    
 } else {
    the_stream = istream;
    the_pos = *fpos;
 }
 
 /* Move the file position indicator */
 if ( status = fsetpos(the_stream,&the_pos) ) {
 	fprintf(stderr,ERRMSG_IO_ERROR,filename);
 	return(ERRNO_IO_ERROR);
 }
 
 /* find number of lines */
 i=0;
 while (fgets( line, 2*MAXLENGTH, the_stream ) != NULL) { i++; }
 if (*ptr2vec != NULL ) { nitem = (i<=*n) ? i : *n; }
 else                   { nitem = i; *n=nitem;      }
 /* rewind */
 fsetpos(the_stream,&the_pos);

 /* allocate memory for vector */
 if (*ptr2vec == NULL ) { *ptr2vec = dvector(nitem); }
 
 /* read file */
 parse_line = svector(MAXCOLS,MAXLENGTH);
 for (i=0; i<nitem; i++) {
   if ( fgets( line, 2*MAXLENGTH, the_stream ) == NULL ) {
   	fprintf(stderr,ERRMSG_IO_ERROR,filename);
	break;
   }
   splitstr( line, parse_line, SPACES );
   *(*ptr2vec+i) = atof( parse_line[colno-1] );
 }
 free_svector(parse_line);
 
 /* close file, if istream NULL */
 if (istream == NULL) { 
    fclose(the_stream);
    the_stream=NULL;
 } else {
    fgetpos(the_stream,&the_pos);
    *fpos = the_pos;
 }
 
 return(status);
}
