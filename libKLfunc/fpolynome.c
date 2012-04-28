/* Polynome */
#include <math.h>

void fpolynome(double x, double afunc[], int na)
{
 int i;

 afunc[0]=1.;
 for (i=1;i<na;i++) afunc[i]=(double)pow((double)x,(double)i);
 
 return;
}
