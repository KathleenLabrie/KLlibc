/* nrutil.c (Partial) modify by your host*/

#include "./myutil.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#define FREE_ARG char*

int IMIN_VECTOR(int v[], unsigned long l)
/* Find smallest value in v */
{
 unsigned long i;
 int m=v[0];
 for (i=1;i<l;i++) m=IMIN(m,v[i]);
 return(m);
}

int IMAX_VECTOR(int v[], unsigned long l)
/* Find largest value in v */
{
 unsigned long i;
 int m=v[0];
 for (i=1;i<l;i++) m=IMAX(m,v[i]);
 return(m);
}


double DMIN_VECTOR(double v[], unsigned long l)
/* Find smallest value in v */
{
 unsigned long i;
 double m=v[0];
 for (i=1;i<l;i++) m=DMIN(m,v[i]);
 return(m);
}

double DMAX_VECTOR(double v[], unsigned long l)
/* Find largest value in v */
{
 unsigned long i;
 double m=v[0];
 for (i=1;i<l;i++) m=DMAX(m,v[i]);
 return(m);
}

double DMIN_MATRIX(double **m, unsigned long naxes[])
/* Find smallest value in m */
{
 unsigned long ii,jj;
 double min=*(*(m+0)+0);
 for (jj=0;jj<naxes[1];jj++)
   for (ii=0;ii<naxes[0];ii++)
     min=DMIN(min, *(*(m+jj)+ii));
 return(min);
}

double DMAX_MATRIX(double **m, unsigned long naxes[])
/* Find largest value in m */
{
 unsigned long ii,jj;
 double max=*(*(m+0)+0);
 for (jj=0;jj<naxes[1];jj++)
   for (ii=0;ii<naxes[0];ii++)
     max=DMAX(max, *(*(m+jj)+ii));
 return(max);
}

void rterror(char error_text[])
/* Numerical Recipes standard error handler */
{
  fprintf(stderr,"Run-time error...\n");
  fprintf(stderr,"%s\n",error_text);
  fprintf(stderr,"...now exiting to system...\n");
  exit(1);
}

char ynquestion(char question[])
/* Retrieve the answer to a y/n question */
{
 char ans[5];
 printf("%s",question);
 scanf("%s",&ans);
 return(ans[0]);
}

char *cvector(long int nh)
/* allocate a character vector with subscript range v[0..nh-1] */
{
  char *v;
  v=(char *)malloc((size_t) (nh*sizeof(char)));
  if (!v) rterror("allocation failure in cvector()");
  return (v);
}

int *ivector(long int nh)
/* allocate a integer vector with subscript range v[0..nh-1] */
{
  int *v;
  v=(int *)malloc((size_t) (nh*sizeof(int)));
  if (!v) rterror("allocation failure in ivector()");
  return (v);
}

int *ivectorc(long int nh)
/* allocate a integer vector with subscript range v[0..nh-1] */
/* and initialize to zero */
{
  int *v;
  v=(int *)calloc(1, (size_t) (nh*sizeof(int)));
  if (!v) rterror("allocation failure in ivectorc()");
  return (v);
}

unsigned long int *lvector(long int nh)
/* allocate an unsigned long int vector with subscript range v[0..nh-1] */
{
  unsigned long int *v;

  v=(unsigned long int *)malloc((size_t) (nh*sizeof(unsigned long int)));
  if (!v) rterror("allocation failure in lvector()");
  return (v);
}

unsigned long int *lvectorc(long int nh)
/* allocate an unsigned long int vector with subscript range v[0..nh-1] */
/* and initialize to zero */
{
  unsigned long int *v;

  v=(unsigned long int *)calloc(1, (size_t) (nh*sizeof(unsigned long int)));
  if (!v) rterror("allocation failure in lvector()");
  return (v);
}

float *vector(long int nh)
/* allocate a float vector with subscript range v[0..nh-1] */
{
  float *v;

  v=(float *)malloc((size_t) (nh*sizeof(float)));
  if (!v) rterror("allocation failure in vector()");
  return (v);
}

double *dvector(long int nh)
/* allocate a double vector with subscript range v[0..nh-1]*/
{
  double *v;

  v=(double *)malloc((size_t) (nh*sizeof(double)));
  if (!v) rterror("allocation failure in dvector()");
  return (v);
}

double *dvectorc(long int nh)
/* allocate a double vector with subscript range v[0..nh-1]
 * and initialize to zero */
{
  double *v;

  v=(double *)calloc(1, (size_t) (nh*sizeof(double)));
  if (!v) rterror("allocation failure in dvectorc()");
  return (v);
}


char **svector(long int nrh, long int nch)
/*allocate a string vector (ie array of char) with subscript range
	sv[0..nrh-1][0..nch-1] => nrh strings of length nch */
{
  long int i;
  char **sv;

  /*allocate pointers to rows (1st array element)*/
  sv=(char **) malloc((size_t) (nrh*sizeof (char*)));
  if (!sv) rterror("allocation failure 1 in svector()");

  /*allocate rows and set pointers to them */
  sv[0]=(char *) malloc((size_t)(nrh*nch*sizeof(char)));
  if (!sv[0]) rterror("allocation failure 2 in svector()");

  for (i=0+1;i<nrh;i++) sv[i]=sv[i-1]+nch;

  /*return pointer to array of pointers to row */
  return sv;
}

int **imatrix(long int nrh, long int nch)
/*allocate a int matrix with subscript range m[0..nrh-1][0..nch-1]*/
{
  long int i;
  int **m;

  /*allocate pointers to rows (1st array element)*/
  m=(int **) malloc((size_t) (nrh*sizeof (int*)));
  if (!m) rterror("allocation failure 1 in imatrix()");

  /*allocate rows and set pointers to them */
  m[0]=(int *) malloc((size_t)(nrh*nch*sizeof(int)));
  if (!m[0]) rterror("allocation failure 2 in imatrix()");

  for (i=0+1;i<nrh;i++) m[i]=m[i-1]+nch;

  /*return pointer to array of pointers to rows */
  return m;
}

int **imatrixc(long int nrh, long int nch)
/*allocate a int matrix with subscript range m[0..nrh-1][0..nch-1]
 * and initialize to zero */
{
  long int i;
  int **m;

  /*allocate pointers to rows (1st array element)*/
  m=(int **) calloc(1, (size_t) (nrh*sizeof (int *)));
  if (!m) rterror("allocation failure 1 in imatrix()");

  /*allocate rows and set pointers to them */
  m[0]=(int *) calloc(1, (size_t)(nrh*nch*sizeof(int)));
  if (!m[0]) rterror("allocation failure 2 in imatrix()");

  for (i=0+1;i<nrh;i++) m[i]=m[i-1]+nch;

  /*return pointer to array of pointers to rows */
  return m;
}

long int **lmatrix(long int nrh, long int nch)
/*allocate a long int matrix with subscript range m[0..nrh-1][0..nch-1]*/
{
  long int i;
  long int **m;

  /*allocate pointers to rows (1st array element) */
  m=(long int **) malloc((size_t) (nrh*sizeof (long int *)));
  if (!m) rterror("allocation failure 1 in lmatrix()");

  /*allocate rows and set pointers to them */
  m[0]=(long int *) malloc((size_t)(nrh*nch*sizeof(long int)));
  if (!m[0]) rterror("allocation failure 2 in lmatrix()");

  for (i=0+1;i<nrh;i++) m[i]=m[i-1]+nch;

  /*return pointer to array of pointers to rows */
  return m;
}

unsigned long int **ulmatrixc(long int nrh, long int nch)
/* allocate an unsigned long int matrix with subscript range
 * m[0..nrh-1][0..nch-1], and initialize to zero */
{
  long int i;
  unsigned long int **m;

  /*allocate pointers to rows (1st array element) */
  m=(unsigned long int **) calloc(1, (size_t) (nrh*sizeof (unsigned long int *)));
  if (!m) rterror("allocation failure 1 in ulmatrixc()");

  /*allocate rows and set pointers to them */
  m[0]=(unsigned long int *) calloc(1, (size_t)(nrh*nch*sizeof(unsigned long int)));
  if (!m[0]) rterror("allocation failure 2 in ulmatrixc()");

  for (i=0+1;i<nrh;i++) m[i]=m[i-1]+nch;

  /*return pointer to array of pointers to rows */
  return m;
}

float **matrix(long int nrh, long int nch)
/*allocate a float matrix with subscript range m[0..nrh-1][0..nch-1]*/
{
  long int i;
  float **m;

  /*allocate pointers to rows (1st array element)*/
  m=(float **) malloc((size_t) (nrh*sizeof (float*)));
  if (!m) rterror("allocation failure 1 in matrix()");

  /*allocate rows and set pointers to them */
  m[0]=(float *) malloc((size_t)(nrh*nch*sizeof(float)));
  if (!m[0]) rterror("allocation failure 2 in matrix()");

  for (i=0+1;i<nrh;i++) m[i]=m[i-1]+nch;

  /*return pointer to array of pointers to rows */
  return m;
}

double **dmatrix(long nrh, long nch)
/*allocate a double matrix with subscript range m[0..nrh-1][0..nch-1]*/
{
  long i;
  double **m;

  /*allocate pointers to rows (1st array element)*/
  m=(double **) malloc((size_t) (nrh*sizeof (double*)));
  if (!m) rterror("allocation failure 1 in dmatrix()");

  /*allocate rows and set pointers to them */
  m[0]=(double *) malloc((size_t)(nrh*nch*sizeof(double)));
  if (!m[0]) rterror("allocation failure 2 in dmatrix()");

  for (i=0+1;i<nrh;i++) m[i]=m[i-1]+nch;

  /*return pointer to array of pointers to rows */
  return m;
}

double **dmatrixc(long nrh, long nch)
/* allocate a double matrix with subscript range m[0..nrh-1][0..nch-1]
 * and initialize to zero */
{
  long i;
  double **m;

  /* allocate pointers to rows (1st array element) */
  m=(double **)calloc(1, (size_t) (nrh*sizeof (double*)));
  if (!m) rterror("allocation failure 1 in dmatrixc()");

  /* allocate rows and set pointers to them */
  m[0]=(double *) calloc(1, (size_t)(nrh*nch*sizeof(double)));
  if (!m[0]) rterror("allocation failure 2 in dmatrixc()");

  for (i=0+1;i<nrh;i++) m[i]=m[i-1]+nch;

  /* return pointer to array of pointers to rows */
  return m;
}

double ***dcube(long nzh, long nrh, long nch)
/* allocate a double cube with subscripts rainge c[0..nzh-1][0..nrh-1][0..nch-1]
 */
{
 long i,j;
 double ***c;
 
 /* allocate pointers to slices (1st array element) */
 c=(double ***)malloc((size_t) (nzh*sizeof (double**)));
 if (!c) rterror("allocation failure 1 in dcube()");
 
 /* allocate pointers to rows (2nd array element) */
 c[0]=(double **)malloc((size_t) (nzh*nrh*sizeof (double *)));
 if (!c[0]) rterror("allocation failure 2 in dcube()");

 for (i=0+1;i<nzh;i++) c[i]=c[i-1]+nrh;

  /* allocate rows and set pointers to them */
 c[0][0]=(double *)malloc((size_t) (nzh*nrh*nch*sizeof (double)));
 if (!c[0][0]) rterror("allocation failure 3 in dcube()");
 
 for (j=0+1; j<nzh; j++) { c[j][0] = c[j-1][0] + nrh*nch; }
 for (j=0;j<nzh;j++) {
   for (i=0+1;i<nrh;i++) c[j][i]=c[j][i-1]+nch;
 }
 
 /* return pointer to array of matrices */
 return c;
}

double ***dcubec(long nzh, long nrh, long nch)
/* allocate a double cube with subscripts rainge c[0..nzh-1][0..nrh-1][0..nch-1]
 * and initialize to zero */
{
 long i,j;
 double ***c;
 
 /* allocate pointers to slices (1st array element) */
 c=(double ***)calloc(1, (size_t) (nzh*sizeof (double**)));
 if (!c) rterror("allocation failure 1 in dcubec()");
 
 /* allocate pointers to rows (2nd array element) */
 c[0]=(double **)calloc(1, (size_t) (nzh*nrh*sizeof (double *)));
 if (!c[0]) rterror("allocation failure 2 in dcubec()");

 for (i=0+1;i<nzh;i++) c[i]=c[i-1]+nrh;

  /* allocate rows and set pointers to them */
 c[0][0]=(double *)calloc(1, (size_t) (nzh*nrh*nch*sizeof (double)));
 if (!c[0][0]) rterror("allocation failure 3 in dcubec()");
 
 for (j=0+1; j<nzh; j++) { c[j][0] = c[j-1][0] + nrh*nch; }
 for (j=0;j<nzh;j++) {
   for (i=0+1;i<nrh;i++) c[j][i]=c[j][i-1]+nch;
 }
 
 /* return pointer to array of matrices */
 return c;
}

void free_cvector(char *v)
/* free a character vector allocated with cvector() */
{
  free((FREE_ARG) v);
}

void free_ivector(int *v)
/* free an integer vector allocated with ivector() */
{
  free((FREE_ARG) v);
}

void free_lvector(unsigned long int *v)
/* free an unsigned long vector allocate with lvector() */
{
  free((FREE_ARG) v);
}

void free_vector(float *v)
/* free a float vector allocated with vector() */
{
  free((FREE_ARG) v);
}

void free_dvector(double *v)
/* free a double vector allocated with dvector() */
{
  free((FREE_ARG) v);
}

void free_svector(char **sv)
/* free a string vector allocated with svector() */
{
  free((FREE_ARG) sv);
}

void free_imatrix(int **m)
/* free an integer matrix allocated with imatrix() */
{
  free(m[0]);
  free(m);
}

void free_lmatrix(long int **m)
/* free a long int matrix allocated with lmatrix() */
{
  free(m[0]);
  free(m);
}

void free_ulmatrix(unsigned long int **m)
/* free an unsigned long in matrix allocated with ulmatrix() */
{
  free(m[0]);
  free(m);
}

void free_matrix(float **m)
/* free a float matrix allocated with matrix() */
{
  free(m[0]);
  free(m);
}

void free_dmatrix(double **m)
/* free a double matrix allocated with dmatrix() */
{
  free(m[0]);
  free(m);
}

void free_dcube(double ***c)
/* free a double cube allocated with dcube() */
{
  free(c[0][0]);
  free(c[0]);
  free(c);
}

/* NR wrappers */
double ***df3tensor(long nzh, long nrh, long nch)
{
 double ***c;
 c = dcube(nzh,nrh,nch);
 return(c);
}

void free_df3tensor(double ***c)
{
 free_dcube(c);
}
