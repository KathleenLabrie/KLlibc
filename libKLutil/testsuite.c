/* Test suite for libKLlibc */
/* Usage: testsuite testid */

#include "./KLutil.h"
#include <stdio.h>	/* for stdout, etc */
#include <stdlib.h> /* for gcc4.0, exit */
#include <stddef.h> /* for NULL */
#include <string.h> /* for strncpy, etc */

#define NTESTS 7

int test_result_message(char testname[], int nfailures);

int test_parse_imname();
int test_splitstr();
int test_cnvtimefmt();
int test_delspace();
int test_equals();
int test_findindex();
int test_month();
int test_utc2local();

main(argc,argv)
int argc;
char *argv[];
{
	int status = 0, FLAGS;
	int teststatus = 0;
	int i, n, id;
	int test2run[NTESTS];
	char **otherargs=NULL;
	char **list_of_tests=NULL;

	/* Initialize */
	FLAGS=0;
	otherargs = svector(NTESTS,MAXLENGTH);
	list_of_tests = svector(NTESTS,MAXLENGTH);
	list_of_tests[0] = "test_parse_imname";
	list_of_tests[1] = "test_splitstr";
	list_of_tests[2] = "test_cnvtimefmt";
	list_of_tests[3] = "test_delspace";
	list_of_tests[4] = "test_findindex";
	list_of_tests[5] = "test_month";
	list_of_tests[6] = "test_utc2local";

	/* Read command line */
	i=1;
	n=0;
	while (i < argc) {
		if (!strncmp("--",argv[i],2)) {
			if (!strncmp("--help",argv[i],6)) {
				fprintf(stdout,HELP_TESTSUITE);
				exit(status);
			}
			else if (!strncmp("--debug",argv[i],7)) {
				FLAGS |= 1 << DEBUG;
			}
			else if (!strncmp("--version",argv[i],9)) {
				fprintf(stdout,"libKLutil testsuite v%s\n",KLUTIL_VERSION);
				exit(status);
			}
			else if (!strncmp("--list",argv[i],6)) {
				for (i=0;i<NTESTS;i++) {
					fprintf(stdout,"%d %s\n",i+1,list_of_tests[i]);
					exit(status);
				}
			}
			else {
				fprintf(stderr, ERRMSG_INPUT_ERROR, argv[i]);
				fprintf(stderr, HELP_TESTSUITE);
				exit(ERRNO_INPUT_ERROR);
			}
		} else if (!strncmp("-",argv[i],1)) {
			if (!strncmp("-h",argv[i],2)) {
				fprintf(stdout, HELP_TESTSUITE);
				exit(status);
			}
			else if (!strncmp("-v",argv[i],2)) {
				FLAGS |= 1 << VERBOSE;
			}
			else {
				fprintf(stderr, ERRMSG_INPUT_ERROR, argv[i]);
				fprintf(stderr, HELP_TESTSUITE);
				exit(ERRNO_INPUT_ERROR);
			}
		} else {
			strcpy(otherargs[n++],argv[i]);
		}
		i++;
	}

	/* Parse otherargs */
	if (n == 0) {
		n = NTESTS;
		for (id=0;id<n;id++) {
			test2run[id] = id+1;
		}
	} else {
		for (i=0;i<n;i++) {
			test2run[i] = atoi(otherargs[i]);
		}
	}

	/* Debug messages to check command line parsing */
	if (FLAGS & 1 << DEBUG) {
		for (i=0;i<n;i++) { printf("%d ",test2run[i]); }
		printf ("\n");

	}

	/* Run tests */
	for (i=0;i<n;i++) {
		switch (test2run[i]) {
		case 1:
			teststatus = test_parse_imname(); break;
		case 2:
			teststatus = test_splitstr(); break;
		case 3:
			teststatus = test_cnvtimefmt(); break;
		case 4:
			teststatus = test_delspace(); break;
		case 5:
			teststatus = test_findindex(); break;
		case 6:
			teststatus = test_month(); break;
		case 7:
			teststatus = test_utc2local(); break;
		default:
			printf("ERROR: invalid test ID.\n");
			fflush(stdout);
			exit(1);
		}
	}

	exit(status);
}

/************************************************************/
/* Utility functions */
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

/*************************************************************/
/* Test 1 - parse_imname */
int test_parse_imname()
{
	int teststatus = 0;
	int i,j, nfailures;
	unsigned long *section;
	unsigned long **expected_sections = NULL;
	char imname[MAXLENGTH];
	char **imstrings=NULL;
	char **expected_imnames=NULL;

	int NTEST1 = 4;

	section = lvectorc(4);
	expected_sections = ulmatrixc(NTEST1,4);

	imstrings = svector(NTEST1,MAXLENGTH);
	expected_imnames = svector(NTEST1,MAXLENGTH);

	strcpy(imstrings[0],"image.fits");
	strcpy(imstrings[1],"image");
	strcpy(imstrings[2],"image.fits[1:2,3:4]");
	strcpy(imstrings[3],"image[1:2,3:4]");

	strcpy(expected_imnames[0],"image.fits");
	strcpy(expected_imnames[1],"image");
	strcpy(expected_imnames[2],"image.fits");
	strcpy(expected_imnames[3],"image");

	expected_sections[2][0]=1; expected_sections[2][1]=2;
	expected_sections[2][2]=3; expected_sections[2][3]=4;
	expected_sections[3][0]=1; expected_sections[3][1]=2;
	expected_sections[3][2]=3; expected_sections[3][3]=4;

	nfailures = 0;
	for (i=0;i<NTEST1;i++) {
		parse_imname(imstrings[i],imname,&section);
		if (strcmp(imname,expected_imnames[i])) {
			printf("%s Error\n", imname);
		} else {
			for (j=0;j<4;j++) {
				if (*(section+j) != *(*(expected_sections+i)+j)) {
					nfailures+=1;
				}
			}
		}
	}

	free_lvector(section);
	free_ulmatrix(expected_sections);
	free_svector(imstrings);
	free_svector(expected_imnames);

	teststatus = test_result_message("test_parse_imname",nfailures);

	return(teststatus);
}

/* Test 2 - splitstr */
int test_splitstr()
{
	int teststatus = 0;
	int i, n, nfailures = 0;
	char **words=NULL;
	char **teststrings=NULL;
	char **expected_words0=NULL;
	char **expected_words1=NULL;
	char **expected_words2=NULL;
	char **expected_words3=NULL;
	char **expected_words4=NULL;
	char **expected_words5=NULL;

	int NTEST2 = 6;

	words = svector(10,MAXLENGTH);

	teststrings = svector(NTEST2,MAXLENGTH);
	expected_words0 = svector(1, MAXLENGTH);
	expected_words1 = svector(2, MAXLENGTH);
	expected_words2 = svector(2, MAXLENGTH);
	expected_words3 = svector(3, MAXLENGTH);
	expected_words4 = svector(4, MAXLENGTH);
	expected_words5 = svector(1, MAXLENGTH);

	strcpy(teststrings[0],"");
	strcpy(teststrings[1],"two words");
	strcpy(teststrings[2],"  leading spaces");
	strcpy(teststrings[3],"with a newline\n");
	strcpy(teststrings[4],"using, coma,as,delimiter ");
	strcpy(teststrings[5],"  ");

	strcpy(expected_words0[0],"\0");
	strcpy(expected_words1[0],"two");
	strcpy(expected_words1[1],"words");
	strcpy(expected_words2[0],"leading");
	strcpy(expected_words2[1],"spaces");
	strcpy(expected_words3[0],"with");
	strcpy(expected_words3[1],"a");
	strcpy(expected_words3[2],"newline");
	strcpy(expected_words4[0],"using");
	strcpy(expected_words4[1]," coma");
	strcpy(expected_words4[2],"as");
	strcpy(expected_words4[3],"delimiter ");
	strcpy(expected_words5[0],"\0");

	n = splitstr(teststrings[0], words, SPACES);
	if ((n != 0) || strcmp(words[0],expected_words0[0])) nfailures+=1;
	n = splitstr(teststrings[1], words, SPACES);
	if ((n != 2) || strcmp(words[0],expected_words1[0]) ||
					strcmp(words[1],expected_words1[1])) nfailures+=1;
	n = splitstr(teststrings[2], words, SPACES);
	if ((n != 2) || strcmp(words[0],expected_words2[0]) ||
					strcmp(words[1],expected_words2[1])) nfailures+=1;
	n = splitstr(teststrings[3], words, SPACES);
	if ((n != 3) || strcmp(words[0],expected_words3[0]) ||
						strcmp(words[1],expected_words3[1]) ||
						strcmp(words[2],expected_words3[2])) nfailures+=1;
	n = splitstr(teststrings[4], words, ",");
	if ((n != 4) || strcmp(words[0],expected_words4[0]) ||
						strcmp(words[1],expected_words4[1]) ||
						strcmp(words[2],expected_words4[2]) ||
						strcmp(words[3],expected_words4[3])) nfailures+=1;
	n = splitstr(teststrings[5], words, SPACES);
	if ((n != 0) || strcmp(words[0],expected_words5[0])) nfailures+=1;

	teststatus = test_result_message("test_splitstr",nfailures);

	return(teststatus);
}

/* Test 3 - cnvtimefmt */
int test_cnvtimefmt()
{
	int teststatus = 0;
	int nfailures = 0;
	char **timestrings=NULL;
	char **expected_timestrings=NULL;

	int NTEST3 = 2;

	timestrings = svector(NTEST3,MAXLENGTH);
	expected_timestrings = svector(NTEST3,MAXLENGTH);

	strcpy(timestrings[0],"1972-02-12T18:08:00");
	strcpy(timestrings[1],"18:08:00 (12/02/1972)");
	strcpy(expected_timestrings[0], timestrings[1]);
	strcpy(expected_timestrings[1], timestrings[0]);

	teststatus = cnvtimefmt(timestrings[0], FITS_FMT, IRAF_FMT);
	if (strcmp(timestrings[0],expected_timestrings[0])) nfailures+=1;
	teststatus = cnvtimefmt(timestrings[1], IRAF_FMT, FITS_FMT);
	if (strcmp(timestrings[1],expected_timestrings[1])) nfailures+=1;

	teststatus = test_result_message("test_cnvtimefmt",nfailures);

	free_svector(timestrings);
	free_svector(expected_timestrings);

	return(teststatus);
}

/* Test 4 - delspace */
int test_delspace()
{
	int teststatus = 0;
	int i, nfailures = 0;
	char **teststrings=NULL;
	char **expected_cleanstr=NULL;

	int NTEST4 = 5;

	teststrings = svector(NTEST4,MAXLENGTH);
	expected_cleanstr = svector(NTEST4,MAXLENGTH);

	strcpy(teststrings[0],"nospaces");
	strcpy(teststrings[1],"  leading");
	strcpy(teststrings[2],"after  ");
	strcpy(teststrings[3],"in between");
	strcpy(teststrings[4],"a	tab");
	strcpy(expected_cleanstr[0],"nospaces");
	strcpy(expected_cleanstr[1],"leading");
	strcpy(expected_cleanstr[2],"after");
	strcpy(expected_cleanstr[3],"inbetween");
	strcpy(expected_cleanstr[4],"atab");

	for (i=0;i<NTEST4;i++) {
		delspace(teststrings[i]);
		if (strcmp(teststrings[i],expected_cleanstr[i])) nfailures+=1;
	}

	teststatus = test_result_message("test_delspace",nfailures);

	return(teststatus);
}

/* Test 5 - equals */
int test_equals()
{
	int teststatus = 0;
	int nfailures = 0;

	if (!equals(0.0,0.000)) nfailures+=1;
	if (equals(1.0,0.0)) nfailures+=1;
	if (equals(1.0,1.000001)) nfailures+=1;
	if (equals(0.0,1.0)) nfailures+1;

	teststatus = test_result_message("test_equals",nfailures);

	return(teststatus);
}

/* Test 6 - findindex */
int test_findindex()
{
	int status = 0, teststatus = 0;
	int i, nfailures = 0;
	long int index;
	double dlist[10];

	for (i=0;i<10;i++) {
		dlist[i] = i;
	}
	status = findindex(3.0,dlist,10,&index);
	if ((status != 0) || (index != 3)) nfailures+=1;
	status = 0;
	status = findindex(4.7,dlist,10,&index);
	if (status != ERRNO_INTERNAL_ERROR) nfailures+=1;

	teststatus = test_result_message("test_findindex",nfailures);

	return(teststatus);
}

/* Test 7 - month */
int test_month()
{
	int teststatus = 0;
	int i, nfailures = 0;
	char the_month[MAXLENGTH];
	char **expected_months=NULL;

	expected_months = svector(12, MAXLENGTH);
	strcpy(expected_months[0],"Jan");
	strcpy(expected_months[1],"Feb");
	strcpy(expected_months[2],"Mar");
	strcpy(expected_months[3],"Apr");
	strcpy(expected_months[4],"May");
	strcpy(expected_months[5],"Jun");
	strcpy(expected_months[6],"Jul");
	strcpy(expected_months[7],"Aug");
	strcpy(expected_months[8],"Sep");
	strcpy(expected_months[9],"Oct");
	strcpy(expected_months[10],"Nov");
	strcpy(expected_months[11],"Dec");

	for (i=0;i<12;i++) {
		month(i, the_month);
		if (strcmp(the_month,expected_months[i])) nfailures+=1;
	}

	free_svector(expected_months);

	teststatus = test_result_message("test_month",nfailures);

	return(teststatus);
}

/* Test 8 - utc2local */
int test_utc2local()
{
	int teststatus = 0;
	int nfailures = 0;
	char timestring[MAXLENGTH];

	strcpy(timestring,"2012-01-30T20:12:14");
	printf("UTC %s is converted to ", timestring);
	teststatus = utc2local(timestring,FITS_FMT);
	printf ("%s local.  Is this correct?\n", timestring);

	/*teststatus = test_result_message("test_utc2local",nfailures);*/

	return(teststatus);
}
