/* Test suite for libKLfile */
/* Usage: testsuite testid */

#include "./KLfile.h"
#include <testutil.h>
#include <mydef.h>
#include <myutil.h>
#include <stdio.h>	 /* for stdout, etc */
#include <stdlib.h>  /* for exit */
#include <stddef.h>	 /* for NULL */
#include <string.h>	 /* for strncpy, etc */

#define NTESTS 6

int test_rd_set();
int test_rd_vec();
int test_rdcube();
int test_tail2head();
int test_wrcube();
int test_mergecube();

main(argc,argv)
int argc;
char *argv[];
{
	int status = 0, FLAGS;
	int teststatus = 0;
	int i, n, id, test;
	int nnonstd;
	int test2run[NTESTS];
	char **nonstdargs=NULL, **otherargs=NULL;
	char **list_of_tests=NULL;

	/* Initialize */
	FLAGS=0;
	nonstdargs = svector(NTESTS+1,MAXLENGTH); /* +1 is for --list */
	otherargs = svector(NTESTS,MAXLENGTH);
	list_of_tests = svector(NTESTS,MAXLENGTH);
	list_of_tests[0] = "test_rd_set";
	list_of_tests[1] = "test_rd_vec";
	list_of_tests[2] = "test_rdcube";
	list_of_tests[3] = "test_tail2head";
	list_of_tests[4] = "test_wrcube";
	list_of_tests[5] = "test_mergecube";

	/* Read command line */
	status = test_parse_stdarguments(argc,argv,HELP_TESTSUITE,
				KLFILE_VERSION, &FLAGS, nonstdargs, &nnonstd);
	if (status == CLEAN_EXIT) exit(0);
	if (FLAGS & 1 << DEBUG) {
		printf("nnonstd = %d\n", nnonstd);
		for (i=0;i<nnonstd;i++) {
			printf("%s\n", nonstdargs[i]);
		}
	}

	i=0;
	n=0;
	while (i < nnonstd) {
		if (!strncmp("--",nonstdargs[i],2)) {
			if (!strncmp("--list",nonstdargs[i],6)) {
				for (test=0;test<NTESTS;test++) {
					fprintf(stdout,"%d %s\n",test+1,list_of_tests[test]);
				}
				exit(status);
			}
			else {
				fprintf(stderr, ERRMSG_INPUT_ERROR, nonstdargs[i]);
				fprintf(stderr, HELP_TESTSUITE);
				exit(ERRNO_INPUT_ERROR);
			}
		} else if (!strncmp("-",nonstdargs[i],1)) {
			fprintf(stderr, ERRMSG_INPUT_ERROR, nonstdargs[i]);
			fprintf(stderr, HELP_TESTSUITE);
			exit(ERRNO_INPUT_ERROR);
		} else {
			strcpy(otherargs[n++],nonstdargs[i]);
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
			teststatus = test_rd_set(); break;
		case 2:
			teststatus = test_rd_vec(); break;
		case 3:
			teststatus = test_rdcube(); break;
		case 4:
			teststatus = test_tail2head(); break;
		case 5:
			teststatus = test_wrcube(); break;
		case 6:
			teststatus = test_mergecube(); break;
		default:
			printf("ERROR: invalid test ID.\n");
			fflush(stdout);
			exit(1);
		}
	}

	exit(status);
}

/*************************************************************/
/* Test 1 - rd_set */
int test_rd_set()
{
	int status, teststatus = 0;
	int nfailures = 0;
	int i;
	long int double_nlines;
	double *double_c1=NULL, *double_c2=NULL;
	char inputfile[MAXLENGTH]="testfile.dat";

	int NTEST1 = 1;

	static long int expected_double_nlines = 5;
	static double expected_double_c1[5] = {1.0,2.0,3.0,4.0,5.0};
	static double expected_double_c2[5] = {6.0,7.0,8.0,9.0,10.0};

	status = 0;
	status = rd_set_double(inputfile, &double_c1, &double_c2, &double_nlines);
	if (status) {
		nfailures += 1;
	} else if (double_nlines != expected_double_nlines) {
		nfailures += 1;
	} else {
		for (i=0;i<double_nlines;i++) {
			if (!equals((*double_c1+i),expected_double_c1[i])) {
				status += 1;
			}

		}
		if (status) nfailures += 1;
	}

	/* similar tests for rd_set_* when they exist */

	teststatus = test_result_message("test_rd_set",nfailures);

	return(teststatus);
}

/* Test 2 - rd_vec */
int test_rd_vec()
{
	int status, teststatus = 0;
	int nfailures = 0;
	int i;
	long int string_nlines, double_nlines;
	double *vec_double=NULL;
	char **vec_string=NULL;
	char inputfile[MAXLENGTH]="testfile.dat";
	FILE *istream=NULL;
	fpos_t curpos;

	int NTEST2 = 7;

	static long int expected_string_nlines = 5;
	static long int expected_double_nlines = 5;
	static double expected_double_vec[5] = {1.5,2.4,3.3,4.2,5.1};
	static char *expected_string_vec[] = {"str1","str2","str3","str4","str5"};

	/* Test 2.1 */
	if ( status = rd_vec_string(inputfile,NULL,NULL,3,&vec_string,&string_nlines) ) {
		nfailures += 1;
	} else if (string_nlines != expected_string_nlines) {
		nfailures += 1;
	} else {
		for (i=0;i<string_nlines;i++) {
			if (strcmp(vec_string[i],expected_string_vec[i])) {
				status += 1;
			}
		}
		if (status) nfailures += 1;
	}
	free_svector(vec_string);
	vec_string=NULL;

	/* Test 2.2 */
	if ( (istream = fopen(inputfile,"r")) == NULL ) {
		nfailures += 1;
	} else {
		fgetpos(istream,&curpos);
		if (status = rd_vec_string(inputfile,istream,&curpos,3,&vec_string,&string_nlines) ) {
			nfailures += 1;
		} else if (string_nlines != expected_string_nlines) {
			nfailures += 1;
		} else {
			for (i=0;i<string_nlines;i++) {
				if (strcmp(vec_string[i],expected_string_vec[i])) {
					status += 1;
				}
			}
			if (status) nfailures += 1;
		}
	}
	free_svector(vec_string);
	vec_string=NULL;
	fclose(istream);
	istream=NULL;

	/* Test 2.3 */
	vec_string = svector(expected_string_nlines,MAXLENGTH);
	if (status = rd_vec_string(inputfile,NULL,NULL,3,&vec_string,&string_nlines)) {
		nfailures += 1;
	} else if (string_nlines != expected_string_nlines) {
		nfailures += 1;
	} else {
		for (i=0;i<string_nlines;i++) {
			if (strcmp(vec_string[i],expected_string_vec[i])) {
				status += 1;
			}
		}
		if (status) nfailures += 1;
	}
	free_svector(vec_string);
	vec_string=NULL;

	/* Test 2.4 */
	vec_string = svector(expected_string_nlines,MAXLENGTH);
	if ( (istream = fopen(inputfile,"r")) == NULL ) {
		nfailures += 1;
	} else {
		fgetpos(istream,&curpos);
		if (status = rd_vec_string(inputfile,istream,&curpos,3,&vec_string,&string_nlines) ) {
			nfailures += 1;
		} else if (string_nlines != expected_string_nlines) {
			nfailures += 1;
		} else {
			for (i=0;i<string_nlines;i++) {
				if (strcmp(vec_string[i],expected_string_vec[i])) {
					status += 1;
				}
			}
			if (status) nfailures += 1;
		}
	}
	free_svector(vec_string);
	vec_string=NULL;
	fclose(istream);
	istream=NULL;

	/* Test 2.5 */
	/* vec_string is shorter than the length of the file */
	/* rd_vec needs to know the number of lines to read */
	string_nlines = expected_string_nlines-2;
	vec_string = svector(string_nlines,MAXLENGTH);
	if (status = rd_vec_string(inputfile,NULL,NULL,3,&vec_string,&string_nlines)) {
		nfailures += 1;
	} else if (string_nlines != expected_string_nlines-2) {
		nfailures += 1;
	} else {
		for (i=0;i<string_nlines;i++) {
			if (strcmp(vec_string[i],expected_string_vec[i])) {
				status += 1;
			}
		}
		if (status) nfailures += 1;
	}
	free_svector(vec_string);
	vec_string=NULL;


	/* Test 2.6 */
	if ( status = rd_vec_double(inputfile,NULL,NULL,4,&vec_double,&double_nlines) ) {
		nfailures += 1;
	} else if (double_nlines != expected_double_nlines) {
		nfailures += 1;
	} else {
		for (i=0;i<double_nlines;i++) {
			if (!equals(vec_double[i],expected_double_vec[i])) {
				status += 1;
			}
		}
		if (status) nfailures += 1;
	}
	free_dvector(vec_double);
	vec_double=NULL;

	/* Test 2.7 */
	if ( (istream = fopen(inputfile,"r")) == NULL ) {
		nfailures += 1;
	} else {
		fgetpos(istream,&curpos);
		if (status = rd_vec_double(inputfile,istream,&curpos,4,&vec_double,&double_nlines) ) {
			nfailures += 1;
		} else if (double_nlines != expected_double_nlines) {
			nfailures += 1;
		} else {
			for (i=0;i<double_nlines;i++) {
				if (!equals(vec_double[i],expected_double_vec[i])) {
					status += 1;
				}
			}
			if (status) nfailures += 1;
		}
	}
	free_dvector(vec_double);
	vec_double=NULL;
	fclose(istream);
	istream=NULL;

	teststatus = test_result_message("test_rd_vec",nfailures);

	return(teststatus);
}

/* Test 3 - rdcube */
int test_rdcube()
{
	int status, teststatus = 0;
	int nfailures = 0;
	int i,j,k;
	long int double_a1_n, double_a2_n, double_a3_n;
	double *double_a1=NULL, *double_a2=NULL, *double_a3=NULL;
	double ***double_cube=NULL;
	char inputfile[MAXLENGTH]="testcube.dat";

	static long int expected_double_a1_n = 5;
	static long int expected_double_a2_n = 2;
	static long int expected_double_a3_n = 3;
	static double expected_double_a1[5] = {1,3,5,7,9};
	static double expected_double_a2[2] = {10.,11.};
	static double expected_double_a3[3] = {20,22,24};
	static double expected_double_cube[3][2][5] = {
			1,2,3,4,5,
			6,7,8,9,10,
			11,12,13,14,15,
			16,17,18,19,20,
			21,22,23,24,25,
			26,27,28,29,30
	};

	if (status = rdcube(inputfile,NULL,NULL,&double_cube,
			&double_a1,&double_a2,&double_a3,
			&double_a1_n,&double_a2_n,&double_a3_n)) {
		nfailures += 1;
	} else if ( (double_a1_n != expected_double_a1_n) ||
			    (double_a2_n != expected_double_a2_n) ||
			    (double_a3_n != expected_double_a3_n) ) {
		nfailures += 1;
	} else {
		for (i=0;i<double_a1_n;i++) {
			if (!equals(double_a1[i],expected_double_a1[i])) {
				status += 1;
			}
		}
		for (j=0;j<double_a2_n;j++) {
			if (!equals(double_a2[j],expected_double_a2[j])) {
				status += 1;
			}
		}
		for (k=0;k<double_a3_n;k++) {
			if (!equals(double_a3[k],expected_double_a3[k])) {
				status += 1;
			}
		}
		for (k=0;k<double_a3_n;k++) {
			for (j=0;j<double_a2_n;j++) {
				for (i=0;i<double_a1_n;i++) {
					if (!equals( *(*(*(double_cube+k)+j)+i),
							expected_double_cube[k][j][i]) ) {
						status += 1;
					}
				}
			}
		}
		if (status) nfailures += 1;
	}
	teststatus = test_result_message("test_rdcube",nfailures);

	return(teststatus);
}

/* Test 4 - tail2head */
int test_tail2head()
{
	int status, teststatus = 0;
	int nfailures = 0;
	char copy_cmd[MAXLENGTH], tail2head_cmd[MAXLENGTH], diff_cmd[MAXLENGTH];
	char rm_cmd[MAXLENGTH];
	char originalfile[MAXLENGTH] = "testfile.dat";
	char workfile[MAXLENGTH] = "testfile_work.dat";
	char expectedfile[MAXLENGTH] = "testtail2head.dat";

	sprintf(copy_cmd,"cp %s %s\n",originalfile, workfile);
	status = system(copy_cmd);

	sprintf(tail2head_cmd,"tail2head %s\n",workfile);
	status = system(tail2head_cmd);
	sprintf(diff_cmd,"diff %s %s\n",workfile,expectedfile);
	status = system(diff_cmd);

	if (status) nfailures += 1;
	else {
		sprintf(rm_cmd,"rm %s\n",workfile);
		status = system(rm_cmd);
	}

	teststatus = test_result_message("test_tail2head",nfailures);

	return(teststatus);
}

/* Test 5 - wrcube */
int test_wrcube()
{
	int status, teststatus = 0;
	int nfailures = 0;
	long int i, j, k;
	char outputfile[MAXLENGTH]="output_testcube.dat";
	char expectedfile[MAXLENGTH]="testcube.dat";
	char diff_cmd[MAXLENGTH], rm_cmd[MAXLENGTH];

	static long int output_double_a1_n = 5;
	static long int output_double_a2_n = 2;
	static long int output_double_a3_n = 3;
	static double output_double_a1[5] = {1,3,5,7,9};
	static double output_double_a2[2] = {10.,11.};
	static double output_double_a3[3] = {20,22,24};
	static double output_double_cube[3][2][5] = {
			1,2,3,4,5,
			6,7,8,9,10,
			11,12,13,14,15,
			16,17,18,19,20,
			21,22,23,24,25,
			26,27,28,29,30
	};
	double ***output_double_cube_ptr;
	output_double_cube_ptr = dcube(3,2,5);
	for (k=0;k<output_double_a3_n;k++) {
		for (j=0;j<output_double_a2_n;j++) {
			for (i=0;i<output_double_a1_n;i++) {
				*(*(*(output_double_cube_ptr+k)+j)+i) = output_double_cube[k][j][i];
			}
		}
	}

	if (status = wrcube(outputfile,NULL,NULL, output_double_cube_ptr,
			output_double_a1,output_double_a2,output_double_a3,
			output_double_a1_n,output_double_a2_n,output_double_a3_n)) {
		nfailures += 1;
	} else {
		/* system call to diff output with testcube.dat */
		sprintf(diff_cmd, "diff %s %s\n", outputfile, expectedfile);
		status = system(diff_cmd);
		if (status) nfailures += 1;
		else {
			sprintf(rm_cmd, "rm %s\n",outputfile);
			status = system(rm_cmd);
		}
	}
	free_dcube(output_double_cube_ptr);

	teststatus = test_result_message("test_wrcube",nfailures);

	return(teststatus);
}

/* Test 6 - mergecube */
int test_mergecube()
{
	int status, teststatus = 0;
	int nfailures = 0;
	char mergecube_cmd[MAXLENGTH],diff_cmd[MAXLENGTH],rm_cmd[MAXLENGTH];
	char expectedcube[MAXLENGTH] = "testmergecube.dat";
	char cube1[MAXLENGTH] = "testcube.dat";
	char cube2[MAXLENGTH] = "testcube2.dat";
	char outputcube[MAXLENGTH] = "testmergecube_output.dat";

	sprintf(mergecube_cmd, "mergecube %s %s -o %s\n", cube1, cube2, outputcube);
	status = system(mergecube_cmd);
	sprintf(diff_cmd, "diff %s %s\n",outputcube,expectedcube);
	status = system(diff_cmd);

	if (status) nfailures += 1;
	else {
		sprintf(rm_cmd, "rm %s\n", outputcube);
		status = system(rm_cmd);
	}

	teststatus = test_result_message("test_mergecube",nfailures);

	return(teststatus);
}
