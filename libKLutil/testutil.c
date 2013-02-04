/* testutil.c */
/* Utilities to help write test suites */

#include "./testutil.h"
#include "./mydef.h"
#include <stdio.h>	/* for printf, stdout */
#include <string.h> /* for strcpy */

int test_parse_stdarguments(int argc, char *argv[], char help[],
		char version[], int *FLAGS, char *nonstdargs[], int *nnonstd)
{
	int status = 0;
	int i, n;

	i=0;
	n=0;
	while (++i < argc) {
		if (!strncmp("--",argv[i],2)) {
			if (!strncmp("--help", argv[i], 6)) {
				fprintf(stdout,"%s",help);
				return(CLEAN_EXIT);
			}
			else if (!strncmp("--debug",argv[i],7)) {
				*FLAGS |= 1 << DEBUG;
				continue;
			}
			else if (!strncmp("--version", argv[i],9)) {
				fprintf(stdout,"v%s\n", version);
				return(CLEAN_EXIT);
			}
		} else if (!strncmp("-",argv[i],1)) {
			if (!strncmp("-h",argv[i],2)) {
				fprintf(stdout,"%s",help);
				return(CLEAN_EXIT);
			}
			else if (!strncmp("-v", argv[i],2)) {
				*FLAGS |= 1 << VERBOSE;
				continue;
			}
		}
		strcpy(nonstdargs[n++], argv[i]);
	}

	*nnonstd=n;

	return(status);
}

int test_result_message(char testname[], int nfailures)
{
	int status = 0;

	if (nfailures != 0) {
		status = 1;
		printf ("%s: %d failures\n",testname, nfailures);
	} else {
		printf ("%s: PASS\n",testname);
	}
	return(status);
}
