/* Function : cnvtimefmt */
/* Version: 1.1.1 */
/*	Convert a time-date string from one format to another
 *
 * int cnvtimefmt( char timestr[], char oldfmt[], char newfmt[] )
 *
 * Arguments :
 *	Input : Time string in old format	- char timestr[]
 *		 Old format			- char oldfmt[]
 *		 New format			- char newfmt[]
 *	Output: Time string in new format	- char timestr[]
 *
 * Output :
 *	Error code : 0 if no error; 1 if error;
 *
 * Calling cnvtimefmt
 *	status = cnvtimefmt( time, OLD_FMT, NEW_FMT );
 *
 * Supported formats :
 *	FITS_FMT : "YYYY-MM-DDThh:mm:ss"
 *	IRAF_FMT : "hh:mm:ss (DD/MM/YYYY)"
 *
 * Needs
 *	nothing!
 */

#include "./mytime.h"
#include <stdio.h>      /* for gcc4.0, printf, sscanf, sprintf */
#include <string.h>

int cnvtimefmt( char timestr[], char oldfmt[], char newfmt[] )
{
 int YYYY,MM,DD,hh,mm,ss;

 /* Identify the old format and get time/date elements */
 if (strcmp(oldfmt,FITS_FMT) == 0) {
   sscanf(timestr, FITS_SCAN, &YYYY,&MM,&DD,&hh,&mm,&ss);
 }
 else if (strcmp(oldfmt,IRAF_FMT) == 0) {
   sscanf(timestr, IRAF_SCAN, &hh,&mm,&ss,&DD,&MM,&YYYY);
 }
 else {
   printf("Error : Unknown time-date format - %s.\n", oldfmt);
   return(1);
 }

 /* Identify the new format and create the new time/date string */
 if (strcmp(newfmt,FITS_FMT) == 0) {
   sprintf(timestr, FITS_SCAN, YYYY,MM,DD,hh,mm,ss);
 }
 else if (strcmp(newfmt,IRAF_FMT) == 0) {
   sprintf(timestr, IRAF_SCAN, hh,mm,ss,DD,MM,YYYY);
 }
 else {
   printf("Error : Unknown time-date format - %s.\n", newfmt);
   return(1);
 }

 return(0);
}
