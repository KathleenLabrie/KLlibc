/* mystruct.c */

#include <stdio.h>      /* for gcc4.0, printf */
#include <string.h>     /* for gcc4.0, strlen */
#include "./KLutil.h"

void clipalloc (long int n, CLIP *strct)
/* allocate memory for the various arrays in a CLIP structure */
{
 strct->clip_tclip = ivector(n);
 strct->clip_sigbox = ulmatrixc(n,2);
 strct->clip_lsigma = dvectorc(n);
 strct->clip_hsigma = dvectorc(n);
 return;
}

void free_clip (CLIP *strct)
/* free a CLIP struct allocated with clipalloc() */
{
 free_ivector(strct->clip_tclip);
 free_ulmatrix(strct->clip_sigbox);
 free_dvector(strct->clip_lsigma);
 free_dvector(strct->clip_hsigma);
 return;
}

int gettclip(char *types[], int tclip[], int niter)
{
 int i;
 for (i=0; i<niter; i++) {
   if (!strncmp(types[i], "ccdclip", strlen(types[i]))) {
      tclip[i] = CCDCLIP;
   } else if (!strncmp(types[i], "sigclip", strlen(types[i]))) {
      tclip[i] = SIGCLIP;
   } else if (!strncmp(types[i], "sigclipr", strlen(types[i]))) {
      tclip[i] = SIGCLIPR;
   } else if (!strncmp(types[i], "sigclipb", strlen(types[i]))) {
      tclip[i] = SIGCLIPB;
   } else {
     printf("ERROR: Unknown clipping (%s)\n",types[i]);
     return(1);
   }
 }
 return(0);
}
