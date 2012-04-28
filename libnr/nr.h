/* nr.h */
#ifndef _NR_H_
#define _NR_H_

void nr_fourn(float data[], unsigned long nn[], int ndim, int isign);
void nr_rlft3(float ***data, float **speq, unsigned long nn1,
  unsigned long nn2, unsigned long nn3, int isign);

#endif
