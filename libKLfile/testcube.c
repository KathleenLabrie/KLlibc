/* Main: testcube */
/* Version: 0.1.1 */
/*   Test IO cube function.
 *
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>	/* for gcc4.0, exit */

#define FILENAME "testcube.dat"
#define OUTFILE "testcube_output.dat"

main()
{
 int status=0;
 long int n1,n2,n3;
 double *axis1=NULL, *axis2=NULL, *axis3=NULL;
 double ***data=NULL;

 if (status = rdcube(FILENAME,NULL,NULL,&data,&axis1,&axis2,&axis3,
 			&n1,&n2,&n3) ) {
	exit(status);
 }

 
 if (status = wrcube(OUTFILE,NULL,NULL,data,axis1,axis2,axis3,n1,n2,n3) ) {
 	exit(status);
 }

 exit(status);
}
