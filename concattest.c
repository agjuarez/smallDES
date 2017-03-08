#include <stdio.h>
#include <string.h>

int main () {

   char str1[12] = "Ho";
   char str2[16] = "Wo";
   char str3[12];
   int  len ;


   /* concatenates str1 and str2 */
   strcat( str1, str2);
   strcat( str1, str2);
   strcat( str1, str2);
   printf("strcat( str1, str2):   %s\n", str1 );
   strcpy(str1,str2);
   printf("strcpy: %s\n",str1);
   /* total lenghth of str1 after concatenation */
   len = strlen(str1);
   printf("strlen(str1) :  %d\n", len );

   return 0;
}
