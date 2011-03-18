/* KLfft.h */

#ifndef _KL_FFT_H_
#define _KL_FFT_H_

void dfourn(double data[], unsigned long nn[], int ndim, int isign);
void drlft3(double ***data, double **speq, unsigned long nn1,
			unsigned long nn2, unsigned long nn3, int isign);

/* Image convolution */
int conv2d(double **ppix, double **presp, long int img_naxes[],
	long int resp_naxes[]);
int gconv2d(double **ppix, long int naxes[], double sigma, double ratio,
	double theta, double width);
int mconv2d(double **ppix, long int naxes[], double sigma, double ratio,
	double theta, double beta, double width);

#endif	/* _KL_FFT_H */
