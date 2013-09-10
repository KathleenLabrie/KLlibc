/* KLcfitsio.h */

#ifndef _KL_CFITSIO_H_
#define _KL_CFITSIO_H_

#define KLCFITSIO_VERSION "0.9.0"

#include <fitsio.h>

/* Help for executables */
#define HELP_TESTSUITE \
        "\nUsage: testsuite [-vh] [testid]\n\
           testid         : ID of the test to run.  If not specified, all the \
                                  tests will be run.\n\
           -h             : Print help\n\
           -v             : Toggle on verbose\n\
           --debug        : Toggle on debug messages\n\
           --version  : Print version\n"

#define KEY_LENGTH 9		/* max keyword length (8 + 1 for \0) */
#define STR_LENGTH 71	/* max string value/comment length (+1 for \0) */
				/* Note that value + comment < 70 characters */

typedef struct klfits_header
{
 char keyword[KEY_LENGTH];
 char value_str[STR_LENGTH];	/* TSTRING */
 char value_byte;			/* TBYTE */
 long int value_lint;		/* TLOGICAL, TSHORT, TUSHORT, TINT 
 					   TUINT, TLONG, TULONG */
 double value_double;		/* TFLOAT, TDOUBLE */
 int datatype;
 char comment[STR_LENGTH];
 
 struct klfits_header *next;	/* Allow for linked list */
} KLFITS_HEADER;

int create_image( char newfilename[], double **ppix, long naxes[],
		KLFITS_HEADER headers[], int nheaders);
int edit_image( char filename[], char newfilename[], double **ppix );
int modify_key( char filename[], char old_keyword[], char new_keyword[]);
int read_image( char filename[], double ***ptr2ppix, long naxes[] );
int read_key(char filename[], char keyword[], char value[], char type[],
             char comments[]);
int read_keyword(char filename[], char keyword[], char value[], 
	     char comments[]);
int write_key(char filename[], char keyword[], char value[], char type[], 
             char comment[]);
int write_numbered_key( char filename[], char keyword[], char value[],
             char type[], char comment[]);
void printerror( int status );
void printwarning( int status );
int get_type( char type[]);

KLFITS_HEADER *klfits_header_vector( int nh );
int klfits_update_key( fitsfile *fptr, KLFITS_HEADER header );

KLFITS_HEADER *create_list_klfits_header();
void add_klfits_header( KLFITS_HEADER *e, KLFITS_HEADER **ptr2first );

void free_klfits_header_vector( KLFITS_HEADER *hv );
#endif /* _KL_CFITSIO_H_ */
