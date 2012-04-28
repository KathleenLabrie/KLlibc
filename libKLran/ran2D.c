/* Function: ran2D */
/* Version: 1.0.0
 *
 * 2D ramdom number generator.
 *
 * void ran2D( long int &seed, float &x, float &y )
 *
 */

#include "./KLran.h"		/* for ran2 */

void ran2D( long int *seed, float *x, float *y )
{

 *x = ran2( seed );
 *y = ran2( seed );

 return;
}
  
