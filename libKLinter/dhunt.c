/* Bisection search with initial guess */
/* Returns an index j such that your desired value lies between table
 * entries xx[j] and xx[j+1], where xx[0..n-1] is the full length of the
 * table */
/* Adapted from NR for double precision and 0-array */
/*
 * The index of the vector centered on jlo, the one that one wants to
 * feed to polint, is given by
 *		k = IMIN(IMAX(j-(m-1)/2,0),n-m)
 * where j is the index given by hunt, n is the full length of the vector
 * and m is the length of the shorter vector to be fed to polint.
 *
 * polint would then be called this way
 *		polint(&xx[k],&yy[k],m,....)
 */

#include "./KLinter.h"

void dhunt(double xx[], unsigned long n, double x, unsigned long *jlo)
{
 unsigned long jm,jhi,inc;
 int ascnd;

 ascnd=(xx[n-1] > xx[0]);
 if (*jlo < 0 || *jlo >= n) {
    *jlo=-1;
    jhi=n;
 } else {
    inc=1;
    if (x >= xx[*jlo] == ascnd) {
       if (*jlo == n-1) return;
       jhi=(*jlo)+1;
       while (x >= xx[jhi] == ascnd) {
          *jlo=jhi;
	  inc += inc;
	  jhi=(*jlo)+inc;
	  if (jhi >= n) {
	     jhi=n;
	     break;
	  }
       }
    } else {
       if (*jlo == 0) {
          *jlo=-1;
	  return;
       }
       jhi=(*jlo)--;
       while (x < xx[*jlo] == ascnd) {
          jhi=(*jlo);
	  inc <<= 1;
	  if (inc >= jhi) {
	     *jlo=-1;
	     break;
	  }
	  else *jlo=jhi-inc;
       }
    }
 }
 while (jhi-(*jlo) != 1) {
    jm=(jhi+(*jlo)) >> 1;
    if (x > xx[jm] == ascnd)
       *jlo=jm;
    else
       jhi=jm;
 }

 return;
}
