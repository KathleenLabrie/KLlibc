/* Function: month */
/* Version: 1.0.1 */
/*
 * Convert month number (0-based) to month name
 *
 * void month(int mon, char the_month[]);
 *
 */

#include <stdio.h>
#include <stdlib.h>     /* for gcc4.0, exit */
#include <string.h>     /* for gcc4.0, strcpy */

void month(int mon, char the_month[])
{
 switch (mon) {
   case 0: strcpy(the_month,"Jan"); break;
   case 1: strcpy(the_month,"Feb"); break;
   case 2: strcpy(the_month,"Mar"); break;
   case 3: strcpy(the_month,"Apr"); break;
   case 4: strcpy(the_month,"May"); break;
   case 5: strcpy(the_month,"Jun"); break;
   case 6: strcpy(the_month,"Jul"); break;
   case 7: strcpy(the_month,"Aug"); break;
   case 8: strcpy(the_month,"Sep"); break;
   case 9: strcpy(the_month,"Oct"); break;
   case 10: strcpy(the_month,"Nov"); break;
   case 11: strcpy(the_month,"Dec"); break;
   default:  printf("ERROR: Invalid month.\n"); fflush(stdout); exit(1);
 }

 return;
}
