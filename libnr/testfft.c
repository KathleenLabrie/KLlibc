/* Main : testfft */
/* Version: 0.1.1 */
/*    Test FFT routines
 *
 * Needs:
 */

#include <stdio.h>      /* for printf, gcc 4.0 */
#include <stdlib.h>     /* for exit, gcc 4.0 */
#include "./nr.h"
#include "./nrutil.h"

#define N2 16	/* size of image */
#define N3 16	/* size of image */

/* extern int printf (const char* format,...); */
/* static char string[] = "string"; */

main()
{
 int status=0;
 long int ii,jj;
 float ***data1,**speq1;

/*** Testing nr_rlft3 and nr_fourn ***/
 data1 = nr_f3tensor(1,1,1,N2,1,N3);
 speq1 = nr_matrix(1,1,1,2*N2);

 for (jj=1;jj<=N2;jj++) {
   for (ii=1;ii<=N3;ii++) {
     data1[1][jj][ii] = 0.;
   }
 }

 data1[1][N2/4][N3/4] = 1.;

 nr_rlft3(data1,speq1,1,N2,N3,1);
 nr_rlft3(data1,speq1,1,N2,N3,-1);

 for (jj=1;jj<=N2;jj++) {
   for (ii=1;ii<=N3;ii++) {
     printf("%d %d %f\n",ii,jj,data1[1][jj][ii]*2.0/(N2*N3));
   }
 }

 nr_free_f3tensor(data1,1,1,1,N2,1,N3);
 nr_free_matrix(speq1,1,1,1,2*N2);

 exit(status);
}
