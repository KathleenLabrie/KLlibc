/* Function : wrlog */
/* Version: 1.0.0 */
/*   Log information about processes being done in a logfile.
 *
 * int wrlog(char logfile[], char message[]);
 *
 * Arguments :
 *	Inputs : Name of the logfile	- char logfile[]
 *	         Message			- char message[]
 *
 * Output :
 *	Error code : 0 if no error; 1+ if error;
 *
 * Calling wrlog
 *	status = wrlog(logfile,message);
 *
 * Needs :
 */

#include "./KLimgutil.h"
#include <stdio.h>

int wrlog( char logfile[], char message[] )
{
 FILE *fplog;

 if ((fplog = fopen( logfile, "a+" )) == NULL)	/*append or create*/
 	return(FILE_NOT_OPENED);
 if (fprintf( fplog, "%s", message) < 0)
 	return(WRITE_ERROR);
 if (fclose(fplog))
 	return(FILE_NOT_CLOSED);

 return(0);
}
