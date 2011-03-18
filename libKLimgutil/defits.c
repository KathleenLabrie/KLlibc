/* Main : defits */
/*  HOG's EFITS -> FITS   Header needs to be swapped but not the image.
 *  1- Swap everything
 *  2- Open and read new FITS file
 *  3- Unswap the image
 *  4- Write and close FITS file
 *
 * Command line: efits_img fits_img nbytes
 *
 *	efits_img	: Name of the EFITS image
 *	fits_img	: Name of the FITS image
 *	nbytes		: Length, in bytes, of the EFITS image
 *
 * Needs
 *   %%%libKLutil%%%
 */

#include "./KLimgutil.h"
#include <KLutil.h>
#include <stdio.h>
#include <string.h>

main(argc,argv)
int argc;
char *argv[];
{
 int nbytes,i,ii,j,done,first_byte;
 char *keyword,*wordkey,*lueva,*value;
 char efits_img[MAXLENGTH], fits_img[MAXLENGTH];
 char *to,*from;
 FILE *iostream;

 i=0;
 while (i < argc) {
   if (!strncmp("-o",argv[i],2)) {
     strcpy( fits_img, argv[++i] );
   }
   else if (!strncmp("-n",argv[i],2)) {
     nbytes = atoi(argv[++i]);
   }
   else {
     strcpy( efits_img, argv[i]);
   }
   i++;
 }

 /* Do some checks on the inputs */
 if (!fits_img) { 
   printf("Please give the name of the output FITS file.\n");
   exit(1);
 }
 if (!nbytes) {
   printf("Please give the size of the EFITS file (in bytes),\n");
   exit(1);
 }
 if (!efits_img) {
   printf("Which EFITS file??\n");
   exit(1);
 }

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
   exit(1);
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

 exit(0);
}
 
