/* Polynomial interpolation */

#include "./KLinter.h"
#include <math.h>
#include <myutil.h>

void dpolint(double xa[], double ya[], int n, double x, double *y, double *dy)
{
  int i,m,ns=0;
  double den,dif,dift,ho,hp,w;
  double *c,*d;

  dif=fabs(x-xa[0]);
  c=dvector(n);
  d=dvector(n);
  for (i=0;i<n;i++) {
    if ((dift=fabs(x-xa[i])) < dif) {
      ns=i;
      dif=dift;
    }
    c[i]=ya[i];
    d[i]=ya[i];
  }
    
  *y=ya[ns--];

  for (m=1;m<n;m++) {
    for (i=0;i<n-m;i++) {
      ho=xa[i]-x;
      hp=xa[i+m]-x;
      w=c[i+1]-d[i];
      if ((den=ho-hp) == 0.0) rterror ("Error in routine polint");
      den=w/den;
      d[i]=hp*den;
      c[i]=ho*den;
    }
    *y += (*dy=(2*(ns+1) < (n-m) ? c[ns+1] : d[ns--]));
  }
  free_dvector(c);
  free_dvector(d);
}
