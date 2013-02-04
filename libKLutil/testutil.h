/* testutil.h */

#ifndef _TEST_UTIL_H_
#define _TEST_UTIL_H_

int test_parse_stdarguments(int argc, char *argv[], char help[],
		char version[], int *FLAGS, char *nonstdargs[], int *nnonstd);
int test_result_message(char testname[], int nfailures);

#endif /* _TEST_UTIL_H_ */
