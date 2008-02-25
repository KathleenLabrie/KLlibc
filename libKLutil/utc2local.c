/* Function : utc2local */
/* Version: 1.1.1 */
/* Convert a time string from UTC/GMT to local time
 *
 * utc2local ( char time[], char format[] )
 *
 * Supported formats : "YYYY-MM-DDThh:mm:ss"
 *
 * Supported time zone : PST, PDT, HST
 */

#include "./mydef.h"
#include "./mytime.h"
#include <time.h>
#include <string.h>
#include <stdio.h>

int translate_tm_zone(char tm_zone_str[]);

int utc2local( char timestr[], char format[] )
{
 int status=0;
 int YYYY,MM,DD,hh,mm,ss;
 int tm_zone;
 long deltasec = 0;
 struct tm utctm, nowtm, *loctm;
 time_t utc, now, local;

 time( &now );
 nowtm = *localtime( &now );
 if ((tm_zone = translate_tm_zone((char *)nowtm.tm_zone)) == ERRNO_INTERNAL_ERROR) {
    return(ERRNO_INTERNAL_ERROR);
 }
 deltasec = tm_zone * SEC_PER_HOUR;
 
 if (strcmp(format,"YYYY-MM-DDThh:mm:ss") == 0) {
   sscanf(timestr,FITSIO_IN,&YYYY,&MM,&DD,&hh,&mm,&ss);
   utctm.tm_sec = ss;
   utctm.tm_min = mm;
   utctm.tm_hour = hh;
   utctm.tm_mday = DD;
   utctm.tm_mon = MM - 1;
   utctm.tm_year = YYYY - 1900;
   utc = mktime( &utctm );	/* Linux 2.2.16-3, gcc-2.96-54 */
   local = utc + deltasec;
   loctm = localtime( &local );
   strftime( timestr, LEN_DATE, FITSIO_OUT, loctm );  /* Linux 2.2.16-3 */
   						      /* gcc-2.96-54 */
 } 
 else {
   printf("This date format is not supported.\n");
   return(ERRNO_INTERNAL_ERROR);
 }

 return(status);
}

/* ------------------------------------- */
int translate_tm_zone( char tm_zone_str[] )
{
 if (!strcmp(tm_zone_str,EDT_STR)) { return(EDT); }
 else if (!strcmp(tm_zone_str,EST_STR)) { return(EST); }
 else if (!strcmp(tm_zone_str,PDT_STR)) { return(PDT); }
 else if (!strcmp(tm_zone_str,PST_STR)) { return(PST); }
 else if (!strcmp(tm_zone_str,HST_STR)) { return(HST); }
 else { 
    printf("ERROR:  Unsupported local time zone (%s).\n",tm_zone_str);
    return(ERRNO_INTERNAL_ERROR);
 }
}
