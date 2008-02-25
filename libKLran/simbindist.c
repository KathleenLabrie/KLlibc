/* Main : simbindist */
/* Version : 0.1.0 */
/*   Generate a sequence of deviates respecting a given binned distribution.
 *   Currently only supports bell-shape like distribution.  It doesn't have
 *   to be a gaussian just more or less like one.
 *
 * Usage: simbindist [-v] indist ndeviates [-o outdeviates -b outdist]
 *					   [--ndist=ndist]
 *
 *	indist		: Input distribution in binned formed
 *	ndeviates	: Number of deviated to produce
 *	-b outdist	: Bin the deviates and write in outdist.
 *			  [outdist used as root name if ndist>1]
 *	-h		: Print help.
 *	-o outdeviates	: Output files for the deviates produces
 *			  [outdeviates used as root name if ndist>1]
 *	-v		: Toggle verbose on
 *	--ndist=ndist	: Specify the number of deviate sequences to create.
 *			  [outdist and outdeviates are treated as root name
 *			   if ndist>1]
 *
 * Needs
 *   %%%libKLran%%%
 *   %%%libKLutil%%%
 *
*/

#include "./KLran.h"
#include <KLutil.h>
#include <stdio.h>
#include <stddef.h>	/* for NULL */
#include <string.h>	/* for strcpy(), strncmp() */
#include <stdlib.h>	/* for atoi() */
#include <time.h>	/* for time() */

#define HELP_SIMBINDIST \
"\nUsage: [-v] indist ndeviates [-o outdeviates -b outdist] [--ndist=ndist]\n\
  indist		: Input distribution in binned formed.\n\
  ndeviates		: Number of deviated to produce.\n\
  -b outdist		: Bin the deviates and write in outdist.\n\
  		 	  [outdist used as root name if ndist>1]\n\
  -h			: Print this help.\n\
  -o outdeviates	: Output files for the deviates produces.\n\
 			  [outdeviates used as root name if ndist>1]\n\
  -v			: Toggle verbose on.\n\
  --ndist=ndist		: Specify the number of deviate sequences to create.\n\
  			  [outdist and outdeviates are treated as root name\n\
  			   if ndist>1]\n"

main(argc,argv)
int argc;
char *argv[];
{
 int FLAGS;
 int i,nbins=0,n,ndeviates,ndat=0,m,ndist=1;
 long idum;
 float *xbin=NULL,*ybin=NULL,*yobin=NULL,*deviates=NULL;
 float inter;
 char indist[MAXLENGTH],outdist[MAXLENGTH],outdeviates[MAXLENGTH];
 char line[MAXLENGTH], **p_parse,**p_arguments;
 char filename[MAXLENGTH], mstr[10];
 time_t now;
 FILE *istream=NULL,*ostream=NULL;

 /* Initialize */
 FLAGS=0;
 strcpy(indist,"");
 strcpy(outdist,"");
 strcpy(outdeviates,"");
 p_arguments = svector(2,MAXLENGTH);

 /* Read command line */
 n=0;
 i=1;
 while (i < argc) {
   if (!strncmp("-b",argv[i],2)) { strcpy(outdist,argv[++i]); }
   else if (!strncmp("-h",argv[i],2)) { printf("%s",HELP_SIMBINDIST); exit(0);}
   else if (!strncmp("-o",argv[i],2)) { strcpy(outdeviates,argv[++i]); }
   else if (!strncmp("-v",argv[i],2)) { FLAGS |= 1 << VERBOSE; }
   else if (!strncmp("--ndist",argv[i],7)) {
     p_parse = svector(2,MAXLENGTH);
     splitstr(argv[i],p_parse,"=");
     ndist = atoi(p_parse[1]);
     free_svector(p_parse);
   }
   else {
     strcpy(p_arguments[n++],argv[i]);
   }
   i++;
 }
 
 if (n != 2) {
 	free_svector(p_arguments);
	fprintf(stderr,ERRMSG_MISSING_INPUT,
		"Input distribution or number of deviates to produce");
	printf("%s",HELP_SIMBINDIST);
	exit(ERRNO_MISSING_INPUT);
 } else {
 	strcpy(indist,p_arguments[0]);
	ndeviates = atoi(p_arguments[1]);
	free_svector(p_arguments);
 }

 /* Read the input distribution */
 if ( (istream = fopen(indist,"r")) == NULL ) {
 	fprintf(stderr,ERRMSG_FILE_NOT_FOUND,indist);
	exit(ERRNO_FILE_NOT_FOUND);
 }
 while (fgets( line, MAXLENGTH-1, istream ) != NULL) 
 	nbins++;
 xbin=vector(nbins);
 ybin=vector(nbins);
 rewind(istream);
 p_parse = svector(2,MAXLENGTH);
 for (i=0;i<nbins;i++) { 
   if ( fgets( line, MAXLENGTH-1, istream ) == NULL) {
   	fclose(istream);
   	free_vector(xbin);
	free_vector(ybin);
   	fprintf(stderr,ERRMSG_IO_ERROR,indist);
	exit(ERRNO_IO_ERROR);
   }
   splitstr(line,p_parse,SPACES);
   *(xbin+i) = atof(p_parse[0]);
   *(ybin+i) = atof(p_parse[1]);
   ndat += *(ybin+i);
 }
 fclose(istream);
 fflush(istream);
  
 /* Normalize the distribution */
 for (i=0; i<nbins; i++) { *(ybin+i) /= (float)ndat; }


 /* Get a new sequence */
 for (m=1;m<=ndist;m++) {
   if (FLAGS & 1<<VERBOSE) { printf("Generating sequence #%-d\n",m); }
   idum = -( (long)time(&now) + m );  /* adding m ensures that time has changed */
   deviates=vector(ndeviates);
   n=0;
   while (n<ndeviates) {
     *(deviates+n) = bingdev(xbin,ybin,nbins,&idum);
     n++;
   }

   if (strlen(outdeviates)) {
      strcpy(filename,outdeviates);
      if (ndist > 1) { 
      		sprintf(mstr,"%-d",m);
      		strcat(filename,mstr);
		strcat(filename,".dat");
      }
      if (FLAGS & 1<<VERBOSE) { printf("\tOutput to %s\n",filename); }
      if ( (ostream = fopen(filename,"w")) == NULL ) {
 	free_vector(deviates);
	free_vector(xbin);
	free_vector(ybin);
 	fprintf(stderr,ERRMSG_IO_ERROR,filename);
	exit(ERRNO_IO_ERROR);
      }
   } else { ostream = stdout; }
   for (n=0;n<ndeviates;n++) { fprintf(ostream,"%f\n",*(deviates+n)); }
   if (strlen(outdeviates)) { fclose(ostream); }
   fflush(ostream);

   if (strlen(outdist)) {
      yobin = vector(nbins);
      for (i=0;i<nbins;i++) { *(yobin+i)=0; }
      inter = xbin[1]-xbin[0];
      for (n=0;n<ndeviates;n++) {
        i = (int)( ( *(deviates+n) - (xbin[0]-inter/2.) )/10 );
        yobin[i]++;
      }
     
      strcpy(filename,outdist);
      if (ndist > 1) { 
      		sprintf(mstr,"%-d",m);
		strcat(filename,mstr);
		strcat(filename,".dat");
      }
      if (FLAGS & 1<<VERBOSE) { printf("\tOutput bins to %s\n",filename); }
      if ( (ostream = fopen(filename,"w")) == NULL ) {
 	free_vector(xbin);
	free_vector(ybin);
	free_vector(yobin);
	fprintf(stderr,ERRMSG_IO_ERROR,filename);
	exit(ERRNO_IO_ERROR);
      }
      for (i=0;i<nbins;i++) { fprintf(ostream,"%f  %f\n",*(xbin+i),*(yobin+i)); }
      fclose(ostream);
      fflush(ostream);
      free_vector(yobin);
   }
   free_vector(deviates);   
 }
 
 free_vector(xbin);
 free_vector(ybin);

 exit(0);
}
