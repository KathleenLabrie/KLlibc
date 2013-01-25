#include "./KLcfitsio.h"
#include <stddef.h>
#include <string.h>

main()
{
 int j;
 KLFITS_HEADER *header,*list=NULL;

/* Test KLFITS_HEADER linked list */
 for (j=0;j<10;j++) {
   header = create_list_klfits_header();
   strcpy(header->keyword,"TEST");
   header->value_lint = j;
   add_klfits_header( header, &list );
 }
 
 for (header = list, j=0; header->next != NULL; header=header->next,j++) {
   printf("%d %s %ld %d\n",j,header->keyword,header->value_lint,header->next);
 }
 printf("%d %s %ld %d\n",j,header->keyword,header->value_lint,header->next);


 exit(0);
}
