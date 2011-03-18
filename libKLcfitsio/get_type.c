/* Function: get_type */
/* Version: 1.0.1 */
/*	Translate data type string to cfitsio code
 *
 * int get_type( char type[]);
 *
 * Arguments:
 *   Input: String defining the type	- char type[]
 *
 * Output:
 *   Cfitsio data type code
 *
 * Calling get_type
 *   datatype = get_type( type );
 *
 * Needs the cfitsio header file.
 *	-I/astro/labrie/progc/include
 */

#include <fitsio.h>

int get_type(char type[])
{
 if (!strncmp("string",type,6)) { return(TSTRING); }
 else if (!strncmp("byte",type,4)) { return(TBYTE); }
 else if (!strncmp("short",type,5)) { return(TSHORT); }
 else if (!strncmp("ushort",type,6)) { return(TUSHORT); }
 else if (!strncmp("log",type,3)) { return(TLOGICAL); }
 else if (!strncmp("int",type,3)) { return(TINT); }
 else if (!strncmp("uint",type,4)) { return(TUINT); }
 else if (!strncmp("long",type,4)) { return(TLONG); }
 else if (!strncmp("ulong",type,5)) { return(TULONG); }
 else if (!strncmp("float",type,5)) { return(TFLOAT); }
 else if (!strncmp("double",type,6)) { return(TDOUBLE); }
 else {
   printf("ERROR: Unrecognized data type (%s)\n",type);
   return(-1);
 }
}
