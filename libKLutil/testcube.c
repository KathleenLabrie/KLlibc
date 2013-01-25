/* test cube */

#include "./myutil.h"
#include <stddef.h>	/* for NULL */
#include <stdio.h>  /* for gcc4.0, printf */
#include <stdlib.h> /* for gcc4.0, exit */

/* Two slices of 3 columns and 4 rows */
#define LX 3
#define LY 4
#define LZ 2

void doit(double ***the_cube);

main()
{
 double ***the_cube=NULL;

 the_cube = dcube(LZ,LY,LX);
 doit(the_cube);
 free_dcube(the_cube);
 the_cube=NULL;
 
 the_cube = df3tensor(LZ,LY,LX);
 doit(the_cube);
 free_df3tensor(the_cube);

 exit(0);
}

void doit(double ***the_cube)
{
 long int i,j,k;
 double value=0;

 value=0;
 for (k=0;k<LZ;k++) {
   for (j=0;j<LY;j++) {
     for (i=0;i<LX;i++) {
       value++;
       the_cube[k][j][i] = value;
       *(*(*(the_cube+k)+j)+i) = value;
     }
   }
 }
 
 for (k=0;k<LZ;k++) {
   printf("Slice %ld\n",k+1);
   for (j=0;j<LY;j++) {
     for (i=0;i<LX;i++) {
       printf("%f ",*(*(*(the_cube+k)+j)+i));
     }
     printf("\n");
   }
 }
 
 return;
}
