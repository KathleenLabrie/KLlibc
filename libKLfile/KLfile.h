/* KLfile.h */

#include <stdio.h>

#ifndef _KL_FILE_H_
#define _KL_FILE_H_

#define MAXCOLS 30
#define MAXARGS 10

/* Help for executables */
#define HELP_MERGECUBE \
"\nUsage: mergecube [-vh] cube 1 cube2 [-o newcube]\n\
   cube1       : First cube file\n\
   cube2       : Second cube file\n\
   -o newcube  : New cube file [Default: STDOUT]\n\
   -h          : Print help\n\
   -v          : Toggle on verbose\n\
   --version   : Print version\n"

/* Library routines */
/* Reading */

/*int rd_set_int(char filename[], int **col1, int **col2, int *n);
int rd_set_long_int(char filename[], long int **col1, long int **col2, int *n);
int rd_set_float(char filename[], float **col1, float **col2, int *n);*/
int rd_set_double(char filename[], double **col1, double **col2, long int *n);

int rd_vec_string(char filename[], FILE *istream, fpos_t *fpos,
			long int colno, char ***ptr2vec, long int *n);
int rd_vec_double(char filename[], FILE *istream, fpos_t *fpos,
			long int colno, double **ptr2vec, long int *n);
int rdcube(char filename[], FILE *istream, fpos_t *pos, 
                double ****pcube, double **paxis1, double **paxis2,
                double **paxis3, long int *n1, long int *n2, long int *n3);

/* Writing */
int wrcube(char filename[], FILE *ostream, fpos_t *pos, double ***cube, 
		double *axis1, double *axis2, double *axis3,
		long int n1,long int n2,long int n3);


#endif /*_KL_FILE_H_*/
