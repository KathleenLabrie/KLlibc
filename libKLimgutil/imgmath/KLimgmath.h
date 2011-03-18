/* Header: KLimgmath.h */
/* Version: 1.0.0 */
/* Library: libKLimgmath.a */
/*	Library of image arithmetic routines */

#ifndef _KL_IMGMATH_H_
#define _KL_IMGMATH_H_

#define ILLEGAL_SECTION    100	/* section out of bounce */
#define ILLEGAL_SECTION_XL 101	/* section out of bounce, low x axes */
#define ILLEGAL_SECTION_XH 102	/* section out of bounce, high x axes */
#define ILLEGAL_SECTION_YL 103	/* section out of bounce, low y axes */
#define ILLEGAL_SECTION_YH 104	/* section out of bounce, high y axes */

#define DIVISION_BY_ZERO   201	/* division by zero */

#define IMAGE 1
#define VALUE 2

int img_or_number(char string[]);

int add2Images(double **ppix1, double **ppix2, double **presult,
	long naxes[], unsigned long *section, long dx, long dy);

int addImage(double **ppix1, double op2nb, double **presult,
	long naxes[], unsigned long *section);

int sub2Images(double **ppix1, double **ppix2, double **presult,
	long naxes[], unsigned long *section, long dx, long dy);

int subImage(double **ppix1, double op2nb, double **presult,
	long naxes[], unsigned long *section);

int mul2Images(double **ppix1, double **ppix2, double **presult,
	long naxes[], unsigned long *section, long dx, long dy);

int mulImage(double **ppix1, double op2nb, double **presult,
	long naxes[], unsigned long *section);

int div2Images(double **ppix1, double **ppix2, double **presult,
	long naxes[], unsigned long *section, long dx, long dy);

int divImage(double **ppix1, double op2nb, double **presult,
	long naxes[], unsigned long *section);

#endif /* _KL_IMGMATH_H_ */
