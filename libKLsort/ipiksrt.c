/* Function: ipiksrt */
/* Version: 1.0.1 */
/*   Numerical Recipes | integer array instead of float 
 *   Sorting by straight insertion : less than 20 elements only 
 *   Full C no adaptation-to-Fortran crap.
 *
 * void ipiksrt(int n, int arr[])
 *
 *	n	: length of arr[]
 *	arr	: integer vector of length n, arr[0..n-1]
 *
 * Calling ipiksrt:
 *	ipiksrt(n,arr)
 *
 * Needs:
 */

void ipiksrt(int n, int arr[])
{
  int i,j;
  int a;

  for (j=1;j<n;j++) {
    a=arr[j];
    i=j-1;
    while (i >= 0 && arr[i] > a) {
      arr[i+1]=arr[i];
      i--;
    }
    arr[i+1]=a;
  }
  return;
}
