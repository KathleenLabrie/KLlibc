/* nrutil.h (Partial) modify by your host*/

#ifndef _MY_UTIL_H_
#define _MY_UTIL_H_

static float sqrarg;
#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg)

static double dsqrarg;
#define DSQR(a) ((dsqrarg=(a)) == 0.0 ? 0.0 : dsqrarg*dsqrarg)

#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))

static int imaxarg1,imaxarg2;
#define IMAX(a,b) (imaxarg1=(a),imaxarg2=(b),(imaxarg1) > (imaxarg2) ?\
(imaxarg1) : (imaxarg2))

static int iminarg1,iminarg2;
#define IMIN(a,b) (iminarg1=(a),iminarg2=(b),(iminarg1) < (iminarg2) ?\
(iminarg1) : (iminarg2))

static float maxarg1,maxarg2;
#define FMAX(a,b) (maxarg1=(a),maxarg2=(b),(maxarg1) > (maxarg2) ?\
(maxarg1) : (maxarg2))

static double dmaxarg1,dmaxarg2;
#define DMAX(a,b) (dmaxarg1=(a),dmaxarg2=(b),(dmaxarg1) > (dmaxarg2) ?\
(dmaxarg1) : (dmaxarg2))

static double dminarg1,dminarg2;
#define DMIN(a,b) (dminarg1=(a),dminarg2=(b),(dminarg1) < (dminarg2) ?\
(dminarg1) : (dminarg2))

int IMIN_VECTOR(int v[], unsigned long l);
int IMAX_VECTOR(int v[], unsigned long l);
double DMIN_VECTOR(double v[], unsigned long l);
double DMAX_VECTOR(double v[], unsigned long l);
double DMIN_MATRIX(double **m, unsigned long naxes[]);
double DMAX_MATRIX(double **m, unsigned long naxes[]);

void rterror (char error_text[]);
char ynquestion (char question[]);
char *cvector(long int nh);
int *ivector(long int nh);
int *ivectorc(long int nh);
unsigned long int *lvector(long int nh);
unsigned long int *lvectorc(long int nh);
float *vector(long int nh);
double *dvector(long int nh);
double *dvectorc(long int nh);
char **svector(long int nrh, long int nch);
int **imatrix(long int nrh, long int nch);
int **imatrixc(long int nrh, long int nch);
long int **lmatrix(long int nrh, long int nch);
unsigned long int **ulmatrixc(long int nrh, long int nch);
float **matrix(long int nrh, long int nch);
double **dmatrix(long nrh, long nch);
double **dmatrixc(long nrh, long nch);
double ***dcube(long nzh, long nrh, long nch);
double ***dcubec(long nzh, long nrh, long nch);
void free_cvector(char *v);
void free_ivector(int *v);
void free_lvector(unsigned long int *v);
void free_vector(float *v);
void free_dvector(double *v);
void free_svector(char **sv);
void free_imatrix(int **m);
void free_lmatrix(long int **m);
void free_ulmatrix(unsigned long int **m);
void free_matrix(float **m);
void free_dmatrix(double **m);
void free_dcube(double ***c);

/* NR wrappers */
double ***df3tensor(long nzh, long nrh, long nch);
void free_df3tensor(double ***c);

#endif /* _MY_UTIL_H_ */
