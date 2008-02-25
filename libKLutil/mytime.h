/* mytime.h */

#ifndef _MY_TIME_H_
#define _MY_TIME_H_

#define FITSIO_IN "%4d-%2d-%2dT%2d:%2d:%2d"
#define FITSIO_OUT "%Y-%m-%dT%H:%M:%S"
#define LEN_DATE 50
#define SEC_PER_HOUR 3600

#define FITS_FMT  "YYYY-MM-DDThh:mm:ss"
#define FITS_SCAN "%4d-%02d-%02dT%02d:%02d:%02d"
#define IRAF_FMT  "hh:mm:ss (DD/MM/YYYY)"
#define IRAF_SCAN "%02d:%02d:%02d (%02d/%02d/%4d)"

#define EDT -4		/* Eastern Daylight-Saving Time */
#define EST -5		/* Eastern Standard Time */
#define PDT -7		/* Pacific Daylight-Saving Time */
#define PST -8		/* Pacific Standard Time */
#define HST -10		/* Hawaii Standard Time */

#define EDT_STR "EDT"		/* Eastern Daylight-Saving Time */
#define EST_STR "EST"		/* Eastern Standard Time */
#define PDT_STR "PDT"		/* Pacific Daylight-Saving Time */
#define PST_STR "PST"		/* Pacific Standard Time */
#define HST_STR "HST"		/* Hawaii Standard Time */

int cnvtimefmt( char timestr[], char oldfmt[], char newfmt[] );
void month(int mon, char the_month[]);
int utc2local( char timestr[], char format[] );

#endif /* _MY_TIME_H_ */
