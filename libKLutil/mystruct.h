/* Structure definitions */

#ifndef _MY_STRUCT_H_
#define _MY_STRUCT_H_

typedef struct
{
 long rstr_oldcol, rstr_newcol;
 long rstr_oldline, rstr_newline;
 int rstr_up;
} RASTER;

typedef struct
{
 unsigned long stats_n;
 double stats_sum, stats_sumsq, stats_ave, stats_var, stats_sdev;
} STATS;

typedef struct
{
 double ccd_rnoise, ccd_gain, ccd_snoise;
} CCD;

typedef struct
{
 int clip_niter;
 unsigned long **clip_sigbox;		/* [niter][2] */
 double *clip_lsigma, *clip_hsigma;	/* [niter] */
 int *clip_tclip;				/* [niter] */
 CCD clip_chip;
} CLIP;

void clipalloc (long int n, CLIP *strct);
void free_clip (CLIP *strct);
int gettclip(char *types[], int tclip[], int niter);

#endif /* _MY_STRUCT_H_ */
