#include "./KLfft.h"
#include <KLutil.h>
#include <KLcfitsio.h>

#define IMGNAME "testconv.fits"
#define OUTIMG "testconvout.fits"

main()
{
 int status=0;
 long naxes[2];
 double **ppix=NULL;
 
 if (status = read_image(IMGNAME,&ppix,naxes) ) {
 	if (ppix!=NULL) free_dmatrix(ppix);
 	printerror(status);
 }
 
 if (status = gconv2d(ppix,naxes,1.,1.,0.,4.)) {
 	if (ppix!=NULL) free_dmatrix(ppix);
	fprintf(stderr,ERRMSG_INTERNAL_ERROR);
	exit(ERRNO_INTERNAL_ERROR);
 }
 
 if (status = edit_image(IMGNAME,OUTIMG,ppix)) {
 	if (ppix!=NULL) free_dmatrix(ppix);
	printerror(status);
 }
 free_dmatrix(ppix);
 
 exit(status);
}
