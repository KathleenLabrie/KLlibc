/* Function: dselect */
/* Version: 1.0.0 */
/* Selecting the kth largest. From NR. 
 */

#define SWAP(a,b) temp=(a);(a)=(b);(b)=temp;

double dselect(unsigned long k, unsigned long n, double arr[])
{
 unsigned long i,ir,j,l,mid;
 double a,temp;

 l=0;
 ir=n-1;
 for(;;) {
   if (ir <= l+1) {
     if (ir == l+1 && arr[ir] < arr[l]) {
       SWAP(arr[l],arr[ir])
     }
     return arr[k-1];
   }
   else {
     mid=(l+ir) >> 1;
     SWAP(arr[mid],arr[l+1])
     if (arr[l+1] > arr[ir]) {
       SWAP(arr[l+1],arr[ir])
     }
     if (arr[l] > arr[ir]) {
       SWAP(arr[l],arr[ir])
     }
     if (arr[l+1] > arr[l]) {
       SWAP(arr[l+1],arr[l])
     }
     i=l+1;
     j=ir;
     a=arr[l];
     for (;;) {
       do i++; while (arr[i] < a);
	do j--; while (arr[j] > a);
	if (j < i) break;
	SWAP(arr[i],arr[j])
     }
     arr[l]=arr[j];
     arr[j]=a;
     if (j >= k-1) ir=j-1;
     if (j <= k-1) l=i;
   }
 }   
}
