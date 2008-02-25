/* Function: dshell */
/* Version: 1.0.0 */
/*   Sorts an array a[0..n-1] into ascending numerical order by Shell's
 *   method (diminishing increment sort). n is input; a is replaces on output 
 *   by its sorted rearrangement.
 *
 *   From NR.  Fortran free.
 *
 */

void dshell(unsigned long n, double a[])
{
 unsigned long i,j,inc;
 double v;

 inc=1;
 do {
    inc *= 3;
    inc++;
 } while (inc <= n);
 do {
    inc /= 3;
    for (i=inc;i<n;i++) {
       v=a[i];
       j=i;
       while (a[j-inc] > v) {
         a[j] = a[j-inc];
	 j -= inc;
	 if (j < inc) break;
       }
       a[j]=v;
    }
 } while (inc > 1);
}
