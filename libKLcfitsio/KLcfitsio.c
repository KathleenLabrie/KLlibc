/* Suite of utility functions for KLcfitsio library */

#include "./KLcfitsio.h"
#include <stdio.h>
#include <fitsio.h>
#include <stdlib.h>

KLFITS_HEADER *klfits_header_vector(int nh)
{
 KLFITS_HEADER *hv;

 hv=(KLFITS_HEADER *) malloc((size_t) (nh*sizeof(KLFITS_HEADER)));
 return(hv);
}

/* Function : klfits_update_key */
/* Version : 0.1.0 */
/*   Update/append a header record of an already open FITS file.
 *
 * int klfits_update_key( fitsfile *fptr, KLFITS_HEADER header )
 *
 * Arguments :
 *   Input :
 *		Pointer to the FITS file		- fitsfile *fptr
 *		Record to add/update			- KLFITS_HEADER header
 *
 * Output :
 *   Error code : 0 if no error; 1+ if error occured;
 *
 * Calling klfits_update_key
 *   status = klfits_update_key( fptr, header );
 *
 * Needs:
 *  %%%libKLcfitsio%%%
 *  %%%libcfitsio%%%
 */
 
int klfits_update_key( fitsfile *fptr, KLFITS_HEADER header )
{
 int status=0;
 
 short int sivalue;
 unsigned short int usivalue;
 int ivalue;			/* for TLOGICAL as well */
 unsigned int uivalue;
 unsigned long int ulivalue;
 float fvalue;

/* long int livalue;		don't need it, header.value_lint is long int */
/* double dvalue;		don't need it, header.value_double is double */
 
 switch (header.datatype) {
   case TSTRING:
   	if ( fits_update_key(fptr, header.datatype, header.keyword,
			header.value_str, header.comment, &status) )
		printerror( status );
   	break;
   case TBYTE:
   	if ( fits_update_key(fptr, header.datatype, header.keyword,
			&(header.value_byte), header.comment, &status) )
		printerror( status );
   	break;   
   case TSHORT:
   	sivalue = (short int)(header.value_lint);
   	if ( fits_update_key(fptr, header.datatype, header.keyword, &sivalue, 
			header.comment, &status) )
		printerror( status );
   	break;
   case TUSHORT:
   	usivalue = (unsigned short int)(header.value_lint);
   	if ( fits_update_key(fptr, header.datatype, header.keyword, &usivalue, 
			header.comment, &status) )
		printerror( status );
   	break;
   case TLOGICAL:
   case TINT:
   	ivalue = (int)(header.value_lint);
   	if ( fits_update_key(fptr, header.datatype, header.keyword, &ivalue, 
			header.comment, &status) )
		printerror( status );
   	break;
   case TUINT:
   	uivalue = (unsigned int)(header.value_lint);
   	if ( fits_update_key(fptr, header.datatype, header.keyword, &uivalue, 
			header.comment, &status) )
		printerror( status );
   	break;
   case TLONG:
   	if ( fits_update_key(fptr, header.datatype, header.keyword, 
			&(header.value_lint), header.comment, &status) )
		printerror( status );
   	break;
   case TULONG:
   	ulivalue = (unsigned long int)(header.value_lint);
   	if ( fits_update_key(fptr, header.datatype, header.keyword, &ulivalue, 
			header.comment, &status) )
		printerror( status );
   	break;
   case TFLOAT:
   	fvalue = (float)(header.value_double);
	if ( fits_update_key(fptr, header.datatype, header.keyword, &fvalue,
			header.comment, &status) )
		printerror( status );
   	break;
   case TDOUBLE:
   	if ( fits_update_key(fptr, header.datatype, header.keyword,
			&(header.value_double), header.comment, &status) )
		printerror( status );
   	break;
   default:
   	status = BAD_DATATYPE;
   	printerror( status );
	break;
 }
 return(status);
}

/* Function Package: list_klfits_header */
/* Version: 0.1.0 */
/*   Linked list for KLFITS_HEADER type.
 *
 * KLFITS_HEADER *create_list_klfits_header()
 * void add_klfits_header(KLFITS_HEADER *e, KLFITS_HEADER **ptr2first)
 *
 * Calling...
 *   KLFITS_HEADER *header,*list=NULL;
 *   header = create_list_klfits_header();
 *   ... 
 *   assign values to header
 *   ...
 *   add_klfits_header( header, &list );
 *   
 */

KLFITS_HEADER *create_list_klfits_header()
{
 KLFITS_HEADER *p;
 p = (KLFITS_HEADER *) malloc( sizeof( KLFITS_HEADER ) );
 if (p==NULL) {
 	fprintf(stderr,"create_list_element: malloc failed.\n");
	exit(1);
 }
 p->next = NULL;
 return p;
}

void add_klfits_header( e, ptr2first )
KLFITS_HEADER *e, **ptr2first;
{
 KLFITS_HEADER *p;
 if (*ptr2first == NULL) {
   *ptr2first = e;
   return;
 }
 for (p = *ptr2first; p->next != NULL; p = p->next);
   ; 
 p->next = e;
}
