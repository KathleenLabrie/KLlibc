#include <fitsio.h>

void printwarning( int status)
{
	/*************************************************/
	/* Print out cfitsio error messages and continue */
	/*************************************************/

	if (status)
	{
	  fits_report_error(stderr, status); /* print error report */
	}
	return;
}
