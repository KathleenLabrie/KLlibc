/* Main: imarith */
/* Version: 1.2.0 */
/*   Do arithmetic on FITS images.  The second operand can be either another
 *   image or a number.  An output name must be specified.  If the name of the
 *   final image is the same as on the operand, the image will be overwritten.
 *
 * Usage: imarith operand1 '+|-|*|/' operand2 result
 *
 *	operand1:	Main image
 *	operand2:	Either another image or a number
 *	result:		Output image.  If same as op. 1 or 2, overwrite.
 *
 * Needs:
 *   %%%libKLutil%%%
 *   %%%libKLcfitsio%%%
 *   %%%libKLimgmath%%%
 */

#include "imgmath/KLimgmath.h"
#include <KLutil.h>
#include <KLcfitsio.h>
#include <stdio.h>
#include <stddef.h>		/* for NULL */
#include <stdlib.h>		/* for stdtod */
#include <string.h>		/* for strncmp */

#define IMAGE 1
#define NUMBER 2
#define BIGNUMBER 1E30

main(argc,argv)
int argc;
char *argv[];
{
 int status=0;
 int op2FLAG=0,sectionFLAG=0;
 unsigned long ii,jj;
 unsigned long naxes1[2], naxes2[2], section[4];
 double **ppix1=NULL, **ppix2=NULL, **presult=NULL;
 double op2nb;
 char op1[MAXLENGTH], op2[MAXLENGTH], result[MAXLENGTH];
 char operator[2];
 char **p_parse;

 /* Read command line */
 if (argc < 5) {	/* Missing input*/
   printf("ERROR: Missing input(s)\n");
   exit(1);
 }
 strcpy( op1, argv[1] );
 strcpy( operator, argv[2] );
 strcpy( op2, argv[3] );
 strcpy( result, argv[4] );
 if (argc > 5) {
   if (!strncmp("--section",argv[5],9)) {
     p_parse = svector(2,MAXLENGTH);
     splitstr(argv[5], p_parse, "=");
     sscanf( p_parse[1], "[%d:%d,%d:%d]", 
     			&section[0],&section[1],&section[2],&section[3] );
     free_svector(p_parse);
     sectionFLAG=1;
   }
   else {
     printf("ERROR: Unknown option. (%s)\n",argv[5]);
     exit(1);
   }
 }

 /* figure out if op2 is image or number */
 op2FLAG = img_or_value(op2);

 if ( !strcmp( op1, result) ) {		/* result = op1 ==> overwrite */
   strcpy(result, "!");
   strcat(result,op1);
 }
 else if ( (op2FLAG == IMAGE) && (!strcmp( op2, result ) ) ) {
   strcpy(result, "!");
   strcat(result,op2);
 }
 if ( op2FLAG == NUMBER ) {
   op2nb = atof(op2);
 }

 /* Open image(s) */
 if ( status = read_image( op1, &ppix1, naxes1 ) ) {
   if (ppix1 != NULL) free_dmatrix(ppix1);
   printerror( status );
 }
 if (op2FLAG == IMAGE) { 
   if ( status = read_image( op2, &ppix2, naxes2 ) ) {
     if (ppix2 != NULL) free_dmatrix(ppix2);
     free_dmatrix(ppix1);
     printerror(status);
   }
   if ((naxes1[0] != naxes2[0]) || (naxes1[1] != naxes2[1])) {
     free_dmatrix(ppix1);
     free_dmatrix(ppix2);
     status=213;		/* BAD_NAXES */
     printerror( status );
   }
 }
 if (!sectionFLAG) {
   section[0]=1;
   section[1]=naxes1[0];
   section[2]=1;
   section[3]=naxes1[1];
 }
   
 /* Allocate memory for output image */
 presult = dmatrixc(section[3]-section[2]+1, section[1]-section[0]+1);

 switch ( operator[0] )
 {
  case '+':
  	if (op2FLAG == IMAGE) {add2Images(ppix1,ppix2,presult,naxes1,section,0,0);}
	else if (op2FLAG == NUMBER) { addImage(ppix1,op2nb,presult,naxes1,section); }
	else { printf("ERROR: Unknown type for operand 2\n"); exit(1);}
	break;
  case '-':
  	if (op2FLAG == IMAGE) { sub2Images(ppix1,ppix2,presult,naxes1,section,0,0); }
	else if (op2FLAG == NUMBER) { subImage(ppix1,op2nb,presult,naxes1,section); }
	else { printf("ERROR: Unknown type for operand 2\n"); exit(1);}
	break;
  case '*':
  	if (op2FLAG == IMAGE) { mul2Images(ppix1,ppix2,presult,naxes1,section,0,0); }
	else if (op2FLAG == NUMBER) { mulImage(ppix1,op2nb,presult,naxes1,section); }
	else { printf("ERROR: Unknown type for operand 2\n"); exit(1);}
	break;
  case '/':
  	if (op2FLAG == IMAGE) { div2Images(ppix1,ppix2,presult,naxes1,section,0,0); }
	else if (op2FLAG == NUMBER) { divImage(ppix1,op2nb,presult,naxes1,section); }
	else { printf("ERROR: Unknown type for operand 2\n"); exit(1);}
	break;
  default :
  	printf("ERROR: Unknown operation\n");
	exit(1);
 }

 /* Desalocate some memory */
 if (op2FLAG == IMAGE) { free_dmatrix(ppix2); }


 /* write output image */
 if ( sectionFLAG ) {
    for (jj=section[2]-1; jj<section[3]; jj++) {
      for (ii=section[0]-1; ii<section[1]; ii++) {
        *(*(ppix1+jj)+ii) = *(*(presult+(jj-section[2]+1))+(ii-section[0]+1));
      }
    }
    if ( status = edit_image(op1, result, ppix1) ) {
      free_dmatrix(ppix1);
      free_dmatrix(presult);
      printerror( status );
    }
 } else {
    if ( status = edit_image(op1, result, presult) ) {
      free_dmatrix(presult);
      printerror( status );
    }
 }

 /* Desalocate all memory */
 free_dmatrix(ppix1);
 free_dmatrix(presult);

 exit(0);
}
