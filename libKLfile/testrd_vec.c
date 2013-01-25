/* testrd_vec */

#include "./KLfile.h"
#include <KLutil.h>
#include <stdio.h>
#include <stdlib.h>	/* for gcc4.0, exit */
#include <string.h>

#define INPUT_FILE "testfile.dat"

main( argc, argv )
int argc;
char *argv[];
{
 int i,status=0;
 long int n;
 double *vec_double=NULL;
 char **vec_string=NULL;
 char file[MAXLENGTH]=INPUT_FILE;
 FILE *istream=NULL;
 fpos_t curpos;

/* rd_vec_string */
/* Test 1 */
 if ( status = rd_vec_string(file,NULL,NULL,3,&vec_string,&n) ) {
 	fprintf(stderr,"ERROR in rd_vec_string\n");
	exit(1);
 }
 printf("rd_vec_string - Test 1 : length=%ld\n",n);
 for (i=0;i<n;i++) { printf("%s\n",vec_string[i]); }
 free_svector(vec_string);
 vec_string=NULL;

/* Test 2 */
 if ( (istream = fopen(file,"r")) == NULL ) {
 	fprintf(stderr,"ERROR opening file\n");
	exit(1);
 }
 fgetpos(istream,&curpos);
 if ( status = rd_vec_string(file,istream,&curpos,3,&vec_string,&n) ) {
 	fprintf(stderr,"ERROR in rd_vec_string\n");
	exit(1);
 }
 printf("rd_vec_string - Test 2 : length=%ld\n",n);
 for (i=0;i<n;i++) { printf("%s\n",vec_string[i]); } 	
 free_svector(vec_string);
 vec_string=NULL;
 fclose(istream);
 istream=NULL;

/* Test 3 */
 vec_string=svector(n,MAXLENGTH);
 if ( status = rd_vec_string(file,NULL,NULL,3,&vec_string,&n) ) {
  	fprintf(stderr,"ERROR in rd_vec_string\n");
	exit(1);
 }
 printf("rd_vec_string - Test 3 : length=%ld\n",n);
 for (i=0;i<n;i++) { printf("%s\n",vec_string[i]); }
 free_svector(vec_string);
 vec_string=NULL;

/* Test 4 */ 
 vec_string=svector(n,MAXLENGTH);
 if ( (istream = fopen(file,"r")) == NULL ) {
 	fprintf(stderr,"ERROR opening file\n");
	exit(1);
 }
 fgetpos(istream,&curpos);
 if ( status = rd_vec_string(file,istream,&curpos,3,&vec_string,&n) ) {
 	fprintf(stderr,"ERROR in rd_vec_string\n");
	exit(1);
 }
 printf("rd_vec_string - Test 4 : length=%ld\n",n);
 for (i=0;i<n;i++) { printf("%s\n",vec_string[i]); } 	
 free_svector(vec_string);
 vec_string=NULL;
 fclose(istream);
 istream=NULL;

/* Test 5 */
 n-=2;
 vec_string=svector(n,MAXLENGTH);
 if ( status = rd_vec_string(file,NULL,NULL,3,&vec_string,&n) ) {
  	fprintf(stderr,"ERROR in rd_vec_string\n");
	exit(1);
 }
 printf("rd_vec_string - Test 5 : length=%ld\n",n);
 for (i=0;i<n;i++) { printf("%s\n",vec_string[i]); }
 free_svector(vec_string);
 vec_string=NULL;

/* rd_vec_double */
/* Test 1 */
 if ( status = rd_vec_double(file,NULL,NULL,4,&vec_double,&n) ) {
 	fprintf(stderr,"ERROR in rd_vec_double\n");
	exit(1);
 }
 printf("rd_vec_double - Test 1 : length=%ld\n",n);
 for (i=0;i<n;i++) { printf("%f\n",vec_double[i]); }
 free_dvector(vec_double);
 vec_double=NULL;
 
/* Test 2 */
 if ( (istream = fopen(file,"r")) == NULL ) {
 	fprintf(stderr,"ERROR opening file\n");
	exit(1);
 }
 fgetpos(istream,&curpos);
 if ( status = rd_vec_double(file,istream,&curpos,4,&vec_double,&n) ) {
 	fprintf(stderr,"ERROR in rd_vec_double\n");
	exit(1);
 }
 printf("rd_vec_double - Test 2 : length=%ld\n",n);
 for (i=0;i<n;i++) { printf("%f\n",vec_double[i]); } 	
 free_dvector(vec_double);
 vec_double=NULL;
 fclose(istream);
 istream=NULL;

 exit(0);
}
