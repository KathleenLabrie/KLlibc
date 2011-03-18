/* Main : mergecube */
/* Version : 0.1.1 */
/*   Merge two cube files into one.
 *
 * Usage: mergecube [-vh] cube1 cube2 [-o newcube]
 *
 *	cube1		: First cube file
 *	cube2		: Second cube file
 *	-o newcube	: New cube file [Default: STDOUT]
 *	-h		: Print help
 *	-v		: Toggle on verbose
 *	--debug		: Toggle on debug mode
 *	--version	: Print version
 *
 * Needs:
 *   %%%libKLutil%%%
 *   %%%libKLfile%%%
 */

#include "./KLfile.h"
#include <stdio.h>
#include <KLutil.h>
#include <KLfile.h>
#include <stdlib.h> /* for gcc4.0, exit */
#include <stddef.h>	/* for NULL */
#include <string.h>

#define VERSION "0.1.0"

static void pre_exit(void);

/* File scope variables */
static unsigned long int *pindex1=NULL,*qindex1=NULL,*rindex1=NULL;
static unsigned long int *pindex2=NULL,*qindex2=NULL,*rindex2=NULL;
static double ***cube1=NULL, ***cube2=NULL, ***newcube=NULL;
static double *paxis1=NULL,*qaxis1=NULL,*raxis1=NULL;
static double *paxis2=NULL,*qaxis2=NULL,*raxis2=NULL;
static double *paxis=NULL,*qaxis=NULL,*raxis=NULL;

main(argc,argv)
int argc;
char *argv[];
{
 int status=0, FLAGS;
 int i, n, ncubes=2;
 int p,q,r,psub,qsub,rsub;
 long int np1,nq1,nr1,np2,nq2,nr2,np,nq,nr;
 double *psortaxis=NULL,*qsortaxis=NULL,*rsortaxis=NULL;
 char **filecubes=NULL,filenewcube[MAXLENGTH];
 char **otherargs=NULL;

 /* Initialize */
 FLAGS=0;
 strcpy(filenewcube,"");
 filecubes = svector(ncubes,MAXLENGTH);
 otherargs = svector(MAXARGS,MAXLENGTH);

 /* Read command line */
 i=1;
 n=0;
 while (i < argc) {
   if (!strncmp("--",argv[i],2)) {
      if (!strncmp("--help",argv[i],6)) {
      	fprintf(stdout,HELP_MERGECUBE);
	exit(status);
      }
      else if (!strncmp("--debug",argv[i],7)) { FLAGS |= 1 << DEBUG; }
      else if (!strncmp("--version",argv[i],9)) {
      	fprintf(stdout,"mergecube v%s\n",VERSION);
	exit(status);
      }
      else {
        fprintf(stderr, ERRMSG_INPUT_ERROR, argv[i]);
	fprintf(stderr, HELP_MERGECUBE);
	exit(ERRNO_INPUT_ERROR);
      }
   } else if (!strncmp("-",argv[i],1)) {
      if (!strncmp("-h",argv[i],2)) {
      	fprintf(stdout, HELP_MERGECUBE);
	exit(status);
      }
      else if (!strncmp("-o",argv[i],2)) {
      	strcpy(filenewcube,argv[++i]);
      }
      else if (!strncmp("-v",argv[i],2)) { FLAGS |= 1 << VERBOSE; }
      else {
         fprintf(stderr, ERRMSG_INPUT_ERROR, argv[i]);
	 fprintf(stderr, HELP_MERGECUBE);
	 exit(ERRNO_INPUT_ERROR);
      }
   } else {
      strcpy(otherargs[n++],argv[i]);
   }
   i++;
 }
 
 /* Parse otherargs */
 if (n != 2) {
 	fprintf(stderr, ERRMSG_INPUT_ERROR);
	fprintf(stderr, HELP_MERGECUBE);
	pre_exit();
	exit(ERRNO_INPUT_ERROR);
 }
 for (i=0;i<ncubes;i++) { strcpy(filecubes[i],otherargs[i]); }

 /* Read input cubes */
 if ( status = rdcube(filecubes[0],NULL,NULL,&cube1,&paxis1,&qaxis1,&raxis1,
 			&np1, &nq1, &nr1) ) {
	pre_exit();
	exit(status);
 }
 if ( status = rdcube(filecubes[1],NULL,NULL,&cube2,&paxis2,&qaxis2,&raxis2,
 			&np2, &nq2, &nr2) ) {
	pre_exit();
	exit(status);
 }

 if (FLAGS & 1 << DEBUG) { 
   printf("First cube: \n");
   printf("%d  %d  %d\n",np1,nq1,nr1);
   for (p=0;p<np1;p++) printf("%g  ",*(paxis1+p));
   printf("\n");
   for (q=0;q<nq1;q++) printf("%g  ",*(qaxis1+q));
   printf("\n");
   for (r=0;r<nr1;r++) printf("%g  ",*(raxis1+r)); 
   printf("\n\n");
   printf("Second cube: \n");
   printf("%d  %d  %d\n",np2,nq2,nr2);
   for (p=0;p<np2;p++) printf("%g  ",*(paxis2+p));
   printf("\n");
   for (q=0;q<nq2;q++) printf("%g  ",*(qaxis2+q));
   printf("\n");
   for (r=0;r<nr2;r++) printf("%g  ",*(raxis2+r)); 
   printf("\n\n");
   fflush(stdout);
 }

 
 /* Allocate memory sorting axes */
 psortaxis = dvector(np1+np2);
 qsortaxis = dvector(nq1+nq2);
 rsortaxis = dvector(nr1+nr2);
 
 /* Copy cube axis values to sort axes */
 for (i=0,p=0;p<np1;p++) *(psortaxis + i++) = *(paxis1+p);
 for (p=0;p<np2;p++) *(psortaxis + i++) = *(paxis2+p);
 for (i=0,q=0;q<nq1;q++) *(qsortaxis + i++) = *(qaxis1+q);
 for (q=0;q<nq2;q++) *(qsortaxis + i++) = *(qaxis2+q);
 for (i=0,r=0;r<nr1;r++) *(rsortaxis + i++) = *(raxis1+r);
 for (r=0;r<nr2;r++) *(rsortaxis + i++) = *(raxis2+r);
 
 if (FLAGS & 1 << DEBUG) {
   printf("Sort axes:\n");
   for (p=0;p<np1+np2;p++) printf("%g  ",*(psortaxis+p));
   printf("\n");
   for (q=0;q<nq1+nq2;q++) printf("%g  ",*(qsortaxis+q));
   printf("\n");
   for (r=0;r<nr1+nr2;r++) printf("%g  ",*(rsortaxis+r)); 
   printf("\n\n");
   fflush(stdout);
 }

 /* Sort axis vectors and eliminate duplicate */
 dshell(np1+np2, psortaxis);
 dshell(nq1+nq2, qsortaxis);
 dshell(nr1+nr2, rsortaxis);
 np=dclean(np1+np2, psortaxis);
 nq=dclean(nq1+nq2, qsortaxis);
 nr=dclean(nr1+nr2, rsortaxis);
 
 if ( FLAGS & 1 << DEBUG ) {
   printf("Sorted new axes:\n");
   printf("%d  %d  %d\n",np,nq,nr);
   fflush(stdout);
 }
   
 /* Allocate memory for new cube axes */
 paxis = dvector(np);
 qaxis = dvector(nq);
 raxis = dvector(nr);
 
 /* Copy sorting axes to new cube axes */
 for (p=0;p<np;p++) *(paxis+p) = *(psortaxis+p);
 for (q=0;q<nq;q++) *(qaxis+q) = *(qsortaxis+q);
 for (r=0;r<nr;r++) *(raxis+r) = *(rsortaxis+r); 
  
 /* Free sorting axes */
 free_dvector(psortaxis);
 free_dvector(qsortaxis);
 free_dvector(rsortaxis);
 
 if ( FLAGS & 1 << DEBUG ) {
   for (p=0;p<np;p++) printf("%g  ",*(paxis+p));
   printf("\n");
   for (q=0;q<nq;q++) printf("%g  ",*(qaxis+q));
   printf("\n");
   for (r=0;r<nr;r++) printf("%g  ",*(raxis+r)); 
   printf("\n");
   fflush(stdout);
 }
 
 /* Allocate memory for index vectors */
 pindex1 = lvector(np1);
 qindex1 = lvector(nq1);
 rindex1 = lvector(nr1);
 pindex2 = lvector(np2);
 qindex2 = lvector(nq2);
 rindex2 = lvector(nr2);

 /* Find and assign position indices for input cubes axes */
 status = dvitable(paxis, np, paxis1, np1, pindex1);
 status = dvitable(qaxis, nq, qaxis1, nq1, qindex1);
 status = dvitable(raxis, nr, raxis1, nr1, rindex1);
 status = dvitable(paxis, np, paxis2, np2, pindex2);
 status = dvitable(qaxis, nq, qaxis2, nq2, qindex2);
 status = dvitable(raxis, nr, raxis2, nr2, rindex2);
 if (status) { exit(status); }
 
 if ( FLAGS & 1 << DEBUG ) {
   printf("Index table - First cube: \n");
   for (p=0;p<np1;p++) printf("%d  ",*(pindex1+p));
   printf("\n");
   for (q=0;q<nq1;q++) printf("%d  ",*(qindex1+q));
   printf("\n");
   for (r=0;r<nr1;r++) printf("%d  ",*(rindex1+r));
   printf("\n");
   printf("Index table - Second cube: \n");
   for (p=0;p<np2;p++) printf("%d  ",*(pindex2+p));
   printf("\n");
   for (q=0;q<nq2;q++) printf("%d  ",*(qindex2+q));
   printf("\n");
   for (r=0;r<nr2;r++) printf("%d  ",*(rindex2+r));
   printf("\n");
   fflush(stdout);
 exit(1);
 }

 /* Free input cube axes */
 free_dvector(paxis1); paxis1=NULL;
 free_dvector(qaxis1); qaxis1=NULL;
 free_dvector(raxis1); raxis1=NULL;
 free_dvector(paxis2); paxis2=NULL;
 free_dvector(qaxis2); qaxis2=NULL;
 free_dvector(raxis2); raxis2=NULL;
 
 /* Allocate memory for newcube */
 newcube = dcubec(nr,nq,np);

 /* Merge cubes */
 /* Cube 1 */
 for (rsub=0;rsub<nr1;rsub++) {
 for (qsub=0;qsub<nq1;qsub++) {
 for (psub=0;psub<np1;psub++) {
   r = rindex1[rsub];
   q = qindex1[qsub];
   p = pindex1[psub];
   *(*(*(newcube+r)+q)+p) = *(*(*(cube1+rsub)+qsub)+psub);
 }}}
 
 /* Cube 2 */
 for (rsub=0;rsub<nr2;rsub++) {
 for (qsub=0;qsub<nq2;qsub++) {
 for (psub=0;psub<np2;psub++) {
   r = rindex2[rsub];
   q = qindex2[qsub];
   p = pindex2[psub];
   *(*(*(newcube+r)+q)+p) = *(*(*(cube2+rsub)+qsub)+psub);
 }}}
 
 /* Free input cubes and axis index vectors */
 free_dcube(cube1); cube1=NULL;
 free_dcube(cube2); cube2=NULL;
 free_lvector(pindex1); pindex1=NULL;
 free_lvector(qindex1); qindex1=NULL;
 free_lvector(rindex1); rindex1=NULL;
 free_lvector(pindex2); pindex2=NULL;
 free_lvector(qindex2); qindex2=NULL;
 free_lvector(rindex2); rindex2=NULL;

 /* Write new cube */
 if ( status = wrcube(filenewcube, NULL, NULL, newcube, paxis, qaxis, raxis,
 			np, nq, nr) ) {
	pre_exit();
	exit(status);
 }

 pre_exit();
 exit(status);
}

static void pre_exit(void) {
 if (cube1 != NULL) free_dcube(cube1);
 if (cube2 != NULL) free_dcube(cube2);
 if (newcube != NULL) free_dcube(newcube);
 if (pindex1 != NULL) free_lvector(pindex1);
 if (qindex1 != NULL) free_lvector(qindex1);
 if (rindex1 != NULL) free_lvector(rindex1);
 if (pindex2 != NULL) free_lvector(pindex2);
 if (qindex2 != NULL) free_lvector(qindex2);
 if (rindex2 != NULL) free_lvector(rindex2);
 if (paxis1 != NULL) free_dvector(paxis1);
 if (qaxis1 != NULL) free_dvector(qaxis1);
 if (raxis1 != NULL) free_dvector(raxis1);
 if (paxis2 != NULL) free_dvector(paxis2);
 if (qaxis2 != NULL) free_dvector(qaxis2);
 if (raxis2 != NULL) free_dvector(raxis2);
 if (paxis != NULL) free_dvector(paxis);
 if (qaxis != NULL) free_dvector(qaxis);
 if (raxis != NULL) free_dvector(raxis);
 return;
}
