/* Function: splitstr */
/* Version: 1.1.1
 * 	Split a line into words.  Save the words into a string vector.
 *
 * int splitstr( char line[], > char *p_line[], char delimiter[])
 *
 * Arguments:
 *   Inputs :
 *		line to parse		- char line[]
 *		token			- char delimiter[]
 *   Output :
 *		vector of strings	- char *p_line[]
 *
 * Output :
 *   Number of words found.
 *
 * Calling splitstr :
 *   #include <myutil.h>
 *   ...
 *   char **p_line;
 *   p_line = svector(MAXCOLS, MAXLENGTH);
 *   splitstr(line, p_line, <string>);
 *
 *   For spaces and tab, use SPACES defined in mydef.h
 *
 * Needs :
 *   KLutil library (libKLutil.a)
 *   
 */


#include <string.h>
#include <stddef.h>
#include "./mydef.h"
#include <stdio.h>

int splitstr(char line[], char *p_line[], char delimiter[])
{
  int n=0,i=0,j;
  char *token,tmpstr[strlen(line)+1];

  strcpy(tmpstr,line);

  if (!strcmp(delimiter,SPACES)) {
    j=0;
    while (i < strlen(line)) {
      if ( ((int)line[i] != 32) && ((int)line[i] != 9) && ((int)line[i] != 10) ) {
        tmpstr[j++] = line[i];
      }
      else if (j != 0) { 
        tmpstr[j] = '\0';
	 strcpy(p_line[n++], tmpstr);
	 j=0;
      }
      i++;
    }
    if (j != 0) {		/* last element */
      tmpstr[j] = '\0';
      strcpy(p_line[n++], tmpstr);
    }
    if (n == 0) {		/* blank line */
      tmpstr[0]='\0';
      strcpy(p_line[0],tmpstr);
    }
  }
  else {
    token=strtok(tmpstr,delimiter);
    while (token!=NULL) {
      strcpy(p_line[n++],token);
      token=strtok(NULL,delimiter);
    }
  }
/* Get rid of newline character */
  if (n > 0) {
    strcpy(tmpstr,p_line[n-1]);
    token=strtok(tmpstr,"\n");
    strcpy(p_line[n-1],token);
  }

  return(n);
}
