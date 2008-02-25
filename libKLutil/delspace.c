/* Function: delspace */
/* Version: 0.1.0 */
/*   Remove spaces and tabs from a string */

#include <string.h>

void delspace(char line[])
{
 int i,j;

 for (i=0,j=0; i<strlen(line)+1; i++) {	/* delete spaces(32) and tabs(9) */
   if (((int)line[i] != 32) && ((int)line[i] != 9)) {line[j++] = line[i];}
 }

 return;
}
