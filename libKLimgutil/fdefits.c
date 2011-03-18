/* Function : fdefits.c */
/* Version: 1.0.0 */
/*  HOG's EFITS -> FITS   Header needs to be swapped but not the image.
 *  1- Swap each keyword and value
 *  2- Write new file (true FITS file)
 *
 * int fdefits( char efits_img[], char fits_img[], int nbytes)
 *
 * Arguments:
 *	efits_img	: Name of the EFITS image
 *	fits_img	: Name of the FITS image
 *	nbytes		: Length, in bytes, of the EFITS image
 *
 * Output:
 *	Error code : 0 if no error; 1+ if error;
 *
 * Calling fdefits
 *	status = fdefits(efits_img, fits_img, nbytes);
 *
 * Needs
 *   %%%libKLutil%%%
 */

#include "./KLimgutil.h"
#include <myutil.h>
#include <stdio.h>
#include <string.h>

int fdefits( char efits_img[], char fits_img[], int nbytes) 
{
 int i,ii,j,done,first_byte;
 char *keyword,*wordkey,*lueva,*value;
 char *to,*from;
 FILE *iostream;

 /* allocate memory for swap arrays */
 from = cvector(nbytes);
 to = cvector(nbytes);
 wordkey = cvector(8);
 keyword = cvector(9);
 lueva = cvector(20);
 value = cvector(20);

 iostream = fopen(efits_img, "rb");
 i=0;
 while ( !feof (iostream) ) {
   *(from+i++) = getc(iostream);
 }
 fclose(iostream);

  /* Separate header from image and reformat header */
 i=ii=done=0;
 while (!done) {
 /* get record [01234567= 0..190..49]*/

   /* read keyword */ 
   for (j=0;j<8;j++) {*(wordkey+j) = *(from+i++);}	/* first 8 char */
   swab(wordkey,keyword,8);
   for (j=0;j<8;j++) {*(to+ii++) = *(keyword+j);}
   *(keyword+8) = '\0';
   if (!strncmp("END ",keyword,4)) {
     done=1;				/* end of header information found */
   }


   if (!done) {
     *(to+ii++) = *(from+i++);
     *(to+ii++) = *(from+i++);	/* pass over '= '  (i)=10 */
     /* read value string */
     for (j=0;j<20;j++) {*(lueva+j) = *(from+i++);}/* next 20 char */
     swab(lueva,value,20);
     for (j=0;j<20;j++) { *(to+ii++) = *(value+j);}

     /* copy the rest of the line */
     for (j=0;j<50;j++) { *(to+ii++) = *(from+i++);}
   }
 }

 /* Make sure i and ii are equal */
 if (i != ii) {
   printf("Error: indices differ.\n");
   free_cvector(from);
   free_cvector(to);
   free_cvector(wordkey);
   free_cvector(keyword);
   free_cvector(lueva);
   free_cvector(value);
   return(1);
 }

 /* copy the rest of the file */
 first_byte = i;
 for (i=first_byte; i<nbytes; i++) {
   *(to+i) = *(from+i);
 }

 /* write to file */
 iostream = fopen(fits_img, "wb");
 for (i=0;i<nbytes;i++) {
   putc(*(to+i),iostream);
 }
 fclose(iostream);

 /* free arrays */
 free_cvector(from);
 free_cvector(to);
 free_cvector(wordkey);
 free_cvector(keyword);
 free_cvector(lueva);
 free_cvector(value);

 return(0);
}
 
