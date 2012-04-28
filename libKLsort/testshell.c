#include "./KLsort.h"
#include <stdio.h>      /* for gcc4.0, printf */
#include <stdlib.h>     /* for gcc4.0, exit */

main()
{
 int i,j,n=10;
 double vec[10];

 j=n;
 for (i=0;i<n;i++) { vec[i] = j--; }
 vec[9] = 4;

 for (i=0;i<n;i++) { printf("%f  ",vec[i]); }
 printf("\n");

 dshell( n, vec);

 for (i=0;i<n;i++) { printf("%f  ",vec[i]); }
 printf("\n");
 
 n=dclean(n, vec);
 
 for (i=0;i<n;i++) { printf("%f  ",vec[i]); }
 printf("\n");
 

 exit(0);
}
