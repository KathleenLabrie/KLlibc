/* Test suite for libKLcfitsio */
/* Usage: testsuite [testid] */

#include "./KLcfitsio.h"
#include <testutil.h>
#include <mydef.h>
#include <myutil.h>
#include <stdio.h>	/* for stdout, etc */
#include <stdlib.h> /* for exit */
#include <stddef.h>	/* for NULL */
#include <string.h>	/* for strncpy, etc */

#define NTESTS 1

int test_create_image(double **parray, long int naxes[], KLFITS_HEADER headers[], int nheaders);
int test_edit_image();
int test_get_type();
int test_modify_key();
int test_printerror();
int test_printwarning();
int test_read_image();
int test_read_key();
int test_read_keyword();
int test_write_key();
int test_write_numbered_key();

int test_klfits_header_vector();
int test_klfits_update_key();
int test_create_list_klfits_header();
int test_add_klfits_header();

int test_klfits_header_linkedlist();

int mktestarray();
int mktestheader();

main(argc,argv)
int argc;
char *argv[];
{
	int status = 0, FLAGS;
	int teststatus = 0;
	int i, n, id, test;
	int nnonstd;
	int test2run[NTESTS];
	long int naxes[2];
	double **parray;
	char **nonstdargs=NULL, **otherargs=NULL;
	char **list_of_tests=NULL;
	KLFITS_HEADER *headers;
	int nheaders;

	/* Initialize */
	FLAGS=0;
	nonstdargs = svector(NTESTS+1, MAXLENGTH); /* +1 is for --list */
	otherargs = svector(NTESTS,MAXLENGTH);
	list_of_tests = svector(NTESTS,MAXLENGTH);
	list_of_tests[0] = "test_create_image";
	list_of_tests[1] = "test_edit_image";
	list_of_tests[2] = "test_get_type";
	list_of_tests[3] = "test_modify_key";
	list_of_tests[4] = "test_printerror";
	list_of_tests[5] = "test_printwarning";
	list_of_tests[6] = "test_read_image";
	list_of_tests[7] = "test_read_key";
	list_of_tests[8] = "test_read_keyword";
	list_of_tests[9] = "test_write_key";
	list_of_tests[10] = "test_write_numbered_key";
	list_of_tests[11] = "test_klfits_header_vector";
	list_of_tests[12] = "test_klfits_update_key";
	list_of_tests[13] = "test_create_list_klfits_header";
	list_of_tests[14] = "test_add_klfits_header";
	list_of_tests[15] = "test_klfits_header_linkedlist";

	/* Read command line */
	status = test_parse_stdarguments(argc,argv,HELP_TESTSUITE,
			KLCFITSIO_VERSION, &FLAGS, nonstdargs, &nnonstd);
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
					fprintf(stdout, "%d %s\n",test+1,list_of_tests[test]);
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
		for (i=0;i<n;i++) { printf("%d ", test2run[i]); }
		printf ("\n");
	}

	/* Create test data */
	naxes[0] = 100; naxes[1] = 200;
	nheaders = 5;
	parray = dmatrix(naxes[1],naxes[0]);
	headers = klfits_header_vector(nheaders);
	status = mktestarray(parray,naxes);
	status = mktestheader(headers,nheaders);
	printf("here\n");
	fflush(stdout);

	/* Run tests */
	for (i=0;i<n;i++) {
		switch (test2run[i]) {
		case 1:
			teststatus = test_create_image(parray, naxes, headers, nheaders); break;
		case 2:
			teststatus = test_edit_image(); break;
		case 3:
			teststatus = test_get_type(); break;
		case 4:
			teststatus = test_modify_key(); break;
		case 5:
			teststatus = test_printerror(); break;
		case 6:
			teststatus = test_printwarning(); break;
		case 7:
			teststatus = test_read_image(); break;
		case 8:
			teststatus = test_read_key(); break;
		case 9:
			teststatus = test_read_keyword(); break;
		case 10:
			teststatus = test_write_key(); break;
		case 11:
			teststatus = test_write_numbered_key(); break;
		case 12:
			teststatus = test_klfits_header_vector(); break;
		case 13:
			teststatus = test_klfits_update_key(); break;
		case 14:
			teststatus = test_create_list_klfits_header(); break;
		case 15:
			teststatus = test_add_klfits_header(); break;
		case 16:
			teststatus = test_klfits_header_linkedlist(); break;
		default:
			printf("ERROR: invalid test ID.\n");
			fflush(stdout);
			exit(1);
		}
	}

	free_dmatrix(parray);
	free_klfits_header_vector(headers);
	exit(status);
}

/*************************************************************/
/* Test 1 - create_image */
int test_create_image(double **parray, long int naxes[], KLFITS_HEADER headers[], int nheaders)
{
	int status, teststatus = 0;
	int nfailures = 0;
	char output_image[MAXLENGTH]="test_output_image.fits";

	/*long int naxes[2];*/
	double **pxpix = NULL;
	char expected_image[MAXLENGTH]="testimage.fits";
	char **exclude=NULL;
	char **xheaders=NULL;
	int i, xnheaders;
	fitsfile *fptr;

	int NTEST1 = 1;

	exclude = svector(2,MAXLENGTH);
	exclude[0] = "DATE";
	exclude[1] = "IRAF-TLM";

	status = create_image(output_image, parray, naxes, headers, nheaders);

	if ( fits_open_file(&fptr, expected_image, READONLY, &status) )
		nfailures += 1;
	else if ( fits_hdr2str(fptr, 1, exclude, 2, xheaders, &xnheaders, &status))
		nfailures += 1;
	/*else {
		printf ("here2\n");
		fflush(stdout);
		for (i;i<xnheaders;i++) {
			printf("%s\n",xheaders[i]);
		}
	}*/
    /*status = read_image(expected_image, &pxpix, xnaxes);*/

    /*free_dmatrix(pxpix);*/

	teststatus = test_result_message("test_create_image",nfailures);

	return(teststatus);
}

/*************************************************************/
/* Test 2 - edit_image */
int test_edit_image()
{
	int status, teststatus = 0;
	int nfailures = 0;

	int NTEST2 = 1;

	teststatus = test_result_message("test_edit_image",nfailures);

	return(teststatus);
}

/*************************************************************/
/* Test 3 - get_type */
int test_get_type()
{
	int status, teststatus = 0;
	int nfailures = 0;

	int NTEST3 = 1;

	teststatus = test_result_message("test_get_type",nfailures);

	return(teststatus);
}

/*************************************************************/
/* Test 4 - modify_key */
int test_modify_key()
{
	int status, teststatus = 0;
	int nfailures = 0;

	int NTEST4 = 1;

	teststatus = test_result_message("test_modify_key",nfailures);

	return(teststatus);
}

/*************************************************************/
/* Test 5 - printerror */
int test_printerror()
{
	int status, teststatus = 0;
	int nfailures = 0;

	int NTEST5 = 1;

	teststatus = test_result_message("test_printerror",nfailures);

	return(teststatus);
}

/*************************************************************/
/* Test 6 - printwarning */
int test_printwarning()
{
	int status, teststatus = 0;
	int nfailures = 0;

	int NTEST6 = 1;

	teststatus = test_result_message("test_printwarning",nfailures);

	return(teststatus);
}

/*************************************************************/
/* Test 7 - read_image */
int test_read_image()
{
	int status, teststatus = 0;
	int nfailures = 0;

	int NTEST7 = 1;

	teststatus = test_result_message("test_read_image",nfailures);

	return(teststatus);
}

/*************************************************************/
/* Test 8 - read_key */
int test_read_key()
{
	int status, teststatus = 0;
	int nfailures = 0;

	int NTEST8 = 1;

	teststatus = test_result_message("test_read_key",nfailures);

	return(teststatus);
}

/*************************************************************/
/* Test 9 - read_keyword */
int test_read_keyword()
{
	int status, teststatus = 0;
	int nfailures = 0;

	int NTEST9 = 1;

	teststatus = test_result_message("test_read_keyword",nfailures);

	return(teststatus);
}

/*************************************************************/
/* Test 10 - write_key */
int test_write_key()
{
	int status, teststatus = 0;
	int nfailures = 0;

	int NTEST10 = 1;

	teststatus = test_result_message("test_write_key",nfailures);

	return(teststatus);
}

/*************************************************************/
/* Test 11 - write_numbered_key */
int test_write_numbered_key()
{
	int status, teststatus = 0;
	int nfailures = 0;

	int NTEST11 = 1;

	teststatus = test_result_message("test_write_numbered_key",nfailures);

	return(teststatus);
}

/*************************************************************/
/* Test 12 - klfits_header_vector */
int test_klfits_header_vector()
{
	int status, teststatus = 0;
	int nfailures = 0;

	int NTEST12 = 1;

	teststatus = test_result_message("test_klfits_header_vector",nfailures);

	return(teststatus);
}

/*************************************************************/
/* Test 13 - klfits_update_key */
int test_klfits_update_key()
{
	int status, teststatus = 0;
	int nfailures = 0;

	int NTEST13 = 1;

	teststatus = test_result_message("test_klfits_update_key",nfailures);

	return(teststatus);
}

/*************************************************************/
/* Test 14 - create_list_klfits_header */
int test_create_list_klfits_header()
{
	int status, teststatus = 0;
	int nfailures = 0;

	int NTEST14 = 1;

	teststatus = test_result_message("test_create_list_klfits_header",nfailures);

	return(teststatus);
}

/*************************************************************/
/* Test 15 - add_klfits_header */
int test_add_klfits_header()
{
	int status, teststatus = 0;
	int nfailures = 0;

	int NTEST15 = 1;

	teststatus = test_result_message("test_add_klfits_header",nfailures);

	return(teststatus);
}

/*************************************************************/
/* Test 16 - klfits_header_linkedlist */
int test_klfits_header_linkedlist()
{
	int status, teststatus = 0;
	int nfailures = 0;

	int NTEST16 = 1;

	teststatus = test_result_message("test_klfits_header_linkedlist",nfailures);

	return(teststatus);
}


/*************************************************************/
/*************************************************************/
/* Utility functions */

int mktestarray(double **ppix, long int naxes[])
{
	int status = 0;
	long int i,j;

	for (j=0;j<naxes[1];j++) {
		for (i=0;i<naxes[0];i++) {
			*(*(ppix+j)+i) = j;
		}
	}

	return status;
}

int mktestheader(KLFITS_HEADER headers[], int nheaders)
{
	int status = 0;
	int i;
	char key[8];

	for (i=0;i<nheaders;i++) {
		sprintf(key,"TEST%d",i);
		strcpy(headers[i].keyword,key);
		headers[i].value_lint = i;
		headers[i].datatype = TINT;
	}

	return status;
}





