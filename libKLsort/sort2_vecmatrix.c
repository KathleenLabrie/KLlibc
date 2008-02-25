/* Function: sort2_vecmatrix */
/* Version: 1.0.1 */
/* Based on Numerical Recipes' Quicksort (sort2) 
 * Sorts a vector vec[0..n-1] into ascending order using Quicksort,
 *	while making the corresponding rearrangement of the matrix
 *	mat[0..dim-1][0..n-1]
 * Fortran free
 *
 * void sort2_vecmatrix(unsigned long n, float vec[], float *mat[], int dim)
 *
 *	n	: length of vector, vec[]
 *	vec[]	: vector to sort
 *	*mat[]	: matrix to rearrange based on the sorting of vec[]
 *	dim	: width of the matrix
 *
 * Calling sort2_vecmatrix:
 *	pvec=vector(n);
 *	pmat=matrix(dim,n);
 *	sort2_vecmatrix(n, pvec, pmat, dim);
 *
 * Needs:
 *  %%%libKLutil%%%
 */

#include <KLutil.h>

#define SWAP(a,b) temp=(a);(a)=(b);(b)=temp;
#define M 7
#define NSTACK 50

void sort2_vecmatrix(unsigned long n, float vec[], float *mat[], int dim)
{
  unsigned long i,ir=n-1,j,k,l=0,d;
  int *istack,jstack=0;
  float a,b[dim],temp;

  istack=ivector(NSTACK);
  for (;;) {
    if (ir-l < M) {
      for (j=l+1;j<=ir;j++) {
        a=vec[j];
        for (d=0;d<dim;d++)
          b[d]=mat[d][j];
        for (i=j-1;i>=0;i--) {
          if (vec[i] <= a) break;
          vec[i+1]=vec[i];
          for (d=0;d<dim;d++)
            mat[d][i+1]=mat[d][i];
        }
        vec[i+1]=a;
        for (d=0;d<dim;d++)
          mat[d][i+1]=b[d];
      }
      if (!jstack) {
        free_ivector(istack);
        return;
      }
      ir=istack[jstack];
      l=istack[jstack-1];
      jstack-=2;
    }else {
      k=(l+ir) >> 1;
      SWAP(vec[k],vec[l+1]);
      for (d=0;d<dim;d++) {
        SWAP(mat[d][k],mat[d][l+1]);
      }
      if (vec[l+1] > vec[ir]) {
        SWAP(vec[l+1],vec[ir]);
        for (d=0;d<dim;d++) {
          SWAP(mat[d][l+1],mat[d][ir]);
        }
      }
      if (vec[l] > vec[ir]) {
        SWAP(vec[l],vec[ir]);
        for (d=0;d<dim;d++) {
          SWAP(mat[d][l],mat[d][ir]);
        }
      }
      if (vec[l+1] > vec[l]) {
        SWAP(vec[l+1],vec[l]);
        for (d=0;d<dim;d++) {
          SWAP(mat[d][l+1],mat[d][l]);
        }
      }
      i=l+1;
      j=ir;
      a=vec[l];
      for (d=0;d<dim;d++)
        b[d]=mat[d][l];
      for (;;) {
        do i++; while (vec[i] < a);
        do j--; while (vec[j] > a);
        if (j < i) break;
        SWAP(vec[i],vec[j]);
        for (d=0;d<dim;d++) {
          SWAP(mat[d][i],mat[d][j]);
        }
      }
      vec[l]=vec[j];
      vec[j]=a;
      for (d=0;d<dim;d++) {
        mat[d][l]=mat[d][j];
        mat[d][j]=b[d];
      }
      jstack+=2;
      if (jstack > NSTACK) rterror("NSTACK too small in sort2_vecmatrix");
      if (ir-1+1 >= j-l) {
        istack[jstack]=ir;
        istack[jstack-1]=i;
        ir=j-1;
      }else {
        istack[jstack]=j-1;
        istack[jstack-1]=l;
        l=i;
      }
    }
  }
}
