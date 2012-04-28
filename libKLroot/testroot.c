/* Test suite */

#include "./KLroot.h"
#include <stdio.h>	/* for gcc4.0, printf */
#include <stdlib.h>	/* for gcc4.0, exit */

#define XACC 1.e-6

void quadfdf(double x, double *f, double *df);
void quadfdfv(double x, double *fparam, double *f, double *df);

main(argc,argv)
int argc;
char *argv[];
{
 double rts;
 double brackets[2];
 
 double fparam[5];

 /* test drtsafe */
 brackets[0]=-10.;
 brackets[1]=0.;
 rts = drtsafe(&quadfdf, brackets[0], brackets[1], XACC);
 printf("drtsafe: root[%f,%f]=%f\n",brackets[0],brackets[1],rts);
 brackets[0]=0.;
 brackets[1]=10.;
 rts = drtsafe(&quadfdf, brackets[0], brackets[1], XACC);
 printf("drtsafe: root[%f,%f]=%f\n",brackets[0],brackets[1],rts);

 /* test drtsafevf */
 brackets[0]=-10.;
 brackets[1]=0.;
 fparam[0]=1.;
 fparam[1]=2.;
 fparam[2]=-15.;
 fparam[3]=2.;
 fparam[4]=2.;
 rts =drtsafevf(&quadfdfv,fparam,brackets[0],brackets[1],XACC);
 printf("drtsafevf: root[%f,%f]=%f\n",brackets[0],brackets[1],rts);
 brackets[0]=0.;
 brackets[1]=10.;
 rts = drtsafevf(&quadfdfv,fparam,brackets[0],brackets[1],XACC);
 printf("drtsafevf: root[%f,%f]=%f\n",brackets[0],brackets[1],rts);
 
 exit(0);
}

void quadfdf(double x, double *f, double *df)
{
 /* Quadratic with roots 3,-5 */
 *f = x*x + 2.*x - 15.;
 *df = 2.*x + 2.;

 return;
}

void quadfdfv(double x, double *fp, double *f, double *df)
{
 /* Quadratic with user defined coefficient */
 *f = *(fp+0)*x*x + *(fp+1)*x + *(fp+2);
 *df = *(fp+3)*x + *(fp+4);
 
 return;
}
