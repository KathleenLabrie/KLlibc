/* Function: img_or_value */
/* Version: 1.0.0
 *	Check if the string (operand 2) is an image name or a value
 *
 * int img_or_value(char string[]);
 *
 * Arguments:
 *	Inputs :
 *		Operand 2			- char string[]
 *
 * Output:
 *	Type (IMAGE = 1,  VALUE = 2) or Error code
 *
 * Calling img_or_value
 *	type = img_or_value( string );
 *
 * Needs:
 */

#include "./KLimgmath.h"

int img_or_value(char string[])
{
 int i;

 for (i=0; i<strlen(string)+1; i++) {
   if ( isalpha(string[i]) ) { return(IMAGE); }
 }

 return(VALUE);
}
