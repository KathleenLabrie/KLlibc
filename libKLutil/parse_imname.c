/* Function : parse_imname */
/* Version : 1.0.0 */
/*   Get image name and section a la IRAF 
 *
 * void parse_imname(char imstring[], char imname[], unsigned long **section)
 *
 * Calling parse_imname
 *   parse_imname(imstring, imname, &section);
 */

#include "./myutil.h"
#include "./mydef.h"
#include <string.h>

void parse_imname(char imstring[], char imname[], unsigned long **section)
{
 int n;
 char **p_parse, tmp1[MAXLENGTH], tmp2[MAXLENGTH];

 p_parse = svector(2,MAXLENGTH);
 n=splitstr(imstring, p_parse, "[");
 strcpy(imname, p_parse[0]);
 if (n == 2) {
   *section = lvector(4);
   strcpy(tmp1, p_parse[1]);
   splitstr(tmp1, p_parse, "]");
   strcpy(tmp1, p_parse[0]);
   splitstr(tmp1, p_parse, ",");
   strcpy(tmp1, p_parse[0]);
   strcpy(tmp2, p_parse[1]);
   splitstr(tmp1, p_parse, ":");
   *(*section+0) = atoi(p_parse[0]);
   *(*section+1) = atoi(p_parse[1]);
   splitstr(tmp2, p_parse, ":");
   *(*section+2) = atoi(p_parse[0]);
   *(*section+3) = atoi(p_parse[1]);
 }
 free_svector(p_parse);
 
 return;
}
