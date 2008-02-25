/* nrutil.c */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#define NR_END 1
#define FREE_ARG char*

void nrerror(char error_text[])
/* Numerical Recipes standard error handler */
{
 fprintf(stderr,"Numerical Recipes run-time error ...\n");
 fprintf(stderr,"%s\n",error_text);
 fprintf(stderr,"... now exiting to system ...\n");
 exit(1);
}

float **nr_matrix(long nrl, long nrh, long ncl, long nch)
/* allocate a float matrix with subscript range m[nrl..nrh][ncl..nch] */
{
 long i, nrow=nrh-nrl+1, ncol=nch-ncl+1;
 float **m;
 
 /* allocate pointers to rows */
 m=(float **) malloc((size_t)((nrow+NR_END)*sizeof(float*)));
 if (!m) nrerror("allocation failure 1 in nr_matrix()");
 m += NR_END;
 m -= nrl;
 
 /* allocate rows and set pointers to them */
 m[nrl]=(float *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(float)));
 if (!m[nrl]) nrerror("allocation failure 2 in nr_matrix()");
 m[nrl] += NR_END;
 m[nrl] -= ncl;
 
 for (i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
 
 /* return pointer to array of pointers to rows */
 return m;
}

float ***nr_f3tensor(long nrl, long nrh, long ncl, long nch, long ndl,
	long ndh)
/* allocate a float 3tensor with range t[nrl..nrh][ncl..nch][ndl..ndh] */
{
 long i,j,nrow=nrh-nrl+1,ncol=nch-ncl+1,ndep=ndh-ndl+1;
 float ***t;
 
 /* allocate pointers to pointers to rows */
 t=(float ***) malloc((size_t)((nrow+NR_END)*sizeof(float **)));
 if (!t) nrerror("allocation failure 1 in nr_f3tensor()");
 t += NR_END;
 t -= nrl;
 
 /* allocate pointers to rows and set pointers to them */
 t[nrl]=(float **) malloc((size_t)((nrow*ncol+NR_END)*sizeof(float *)));
 if (!t[nrl]) nrerror("allocation failure 2 in nr_f3tensor()");
 t[nrl] += NR_END;
 t[nrl] -= ncl;
 
 /* allocate rows and set pointers to them */
 t[nrl][ncl]=(float *) malloc((size_t)((nrow*ncol*ndep+NR_END)*sizeof(float)));
 if (!t[nrl][ncl]) nrerror("allocation failure 3 in f3tensor()");
 t[nrl][ncl] += NR_END;
 t[nrl][ncl] -= ndl;
 
 for (j=ncl+1;j<=nch;j++) t[nrl][j]=t[nrl][j-1]+ndep;
 for (i=nrl+1;i<=nrh;i++) {
   t[i]=t[i-1]+ncol;
   t[i][ncl]=t[i-1][ncl]+ncol*ndep;
   for (j=ncl+i;j<=nch;j++) t[i][j]=t[i][j-1]+ndep;
 }
 
 /* return pinter to array of pointers to rows */
 return t;
}

void nr_free_matrix(float **m, long nrl, long nrh, long ncl, long nch)
/* free a float matrix allcoated by nr_matrix() */
{
 free((FREE_ARG) (m[nrl]+ncl-NR_END));
 free((FREE_ARG) (m+nrl-NR_END));
}

void nr_free_f3tensor(float ***t, long nrl, long nrh, long ncl, long nch,
	long ndl, long ndh)
/* free a float f3tensor allocated by nr_f3tensor() */
{
 free((FREE_ARG) (t[nrl][ncl]+ndl-NR_END));
 free((FREE_ARG) (t[nrl]+ncl-NR_END));
 free((FREE_ARG) (t+nrl-NR_END));
}
