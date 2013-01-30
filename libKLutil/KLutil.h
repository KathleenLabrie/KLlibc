/* KLutil.h */

#ifndef _KL_UTIL_H_
#define _KL_UTIL_H_

#ifndef _MY_UTIL_H_
#include "./myutil.h"
#endif

#ifndef _MY_DEF_H_
#include "./mydef.h"
#endif

#ifndef _MY_TIME_H_
#include "./mytime.h"
#endif

#ifndef _MY_STRUCT_H_
#include "./mystruct.h"
#endif

#define KLUTIL_VERSION "0.9.0"

/* Help for executables */
#define HELP_TESTSUITE \
	"\nUsage: testsuite [-vh] [testid]\n\
	   testid	  : ID of the test to run.  If not specified, all the \
				  tests will be run.\n\
	   -h		  : Print help\n\
	   -v		  : Toggle on verbose\n\
	   --debug	  : Toggle on debug messages\n\
	   --version  : Print version\n"

/* User input parsing functions */
void parse_imname(char imstring[], char imname[], unsigned long **section);

/* String Functions */
void delspace(char line[]);
int splitstr(char line[], char *p_line[], char delimiter[]);

/* Math Functions */
int equals(double val1, double val2);

/* Vector Functions */
int findindex(double value, double *vec, long int n, long int *index);

#endif /* _KL_UTILS_H_ */
