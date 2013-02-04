/* mydef.h */

#ifndef _MY_DEF_H_
#define _MY_DEF_H_

#define MAXLENGTH 80
#define TRUE 1
#define FALSE 0
#define SPACES "\40|\11"
#define BIG_NUMBER 1E30
#define SMALL_NUMBER -1E30
#define PI 3.1415926535

/* Old error code */
#define INTERNAL_ERROR 99
#define FILE_NOT_FOUND 101
#define INPUT_ERROR 102

/* Error codes */
#define ERRNO_INTERNAL_ERROR 99
#define ERRNO_FILE_NOT_FOUND 101
#define ERRNO_INPUT_ERROR 102
#define ERRNO_UNDEFINED_INPUT 103
#define ERRNO_MISSING_INPUT 104
#define ERRNO_IO_ERROR 105

/* Error messages */
#define ERRMSG_INTERNAL_ERROR "ERROR: Internal error\n"
#define ERRMSG_FILE_NOT_FOUND "ERROR: File not found. (%s)\n"
#define ERRMSG_INPUT_ERROR "ERROR: Input error (%s)\n"
#define ERRMSG_UNDEFINED_INPUT "ERROR: Undefined input (%s)\n"
#define ERRMSG_MISSING_INPUT "ERROR: Missing input (%s)\n"
#define ERRMSG_IO_ERROR "ERROR: I/O error (%s)\n"

/* Other status codes */
#define CLEAN_EXIT 901		/* when a subroutine needs to tell the
							   calling routine that an exit is required
							   even though there's been no errors. */

#define MAX_ITER 201

/* Useful bit definition */
#define VERBOSE 0
#define INTERACTIVE 1
#define DEBUG 2


/* type of clipping */
#define CCDCLIP 1		/* stddev from ccd charateristics */
#define SIGCLIP 2		/* local stddev */
#define SIGCLIPR 3		/* local stddev with mask from 1st iteration */
#define SIGCLIPB 4		/* local stddev with mask from 2nd++ iterations */

#endif /*_MY_DEF_H_*/
