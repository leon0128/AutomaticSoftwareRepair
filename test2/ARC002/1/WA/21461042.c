#include <stdio.h>

int
main()
{
 int year = 2404; /* ここの値を変えて下さい */

 if (year % 4 == 0) {
   if (year % 100 == 0) {
     if (year % 400 == 0) {
       printf("YES/n");
     } else {
       printf("NO/n");
     }
   } else {
     printf("YES/n");
   }
 } else {
   printf("NO/n");
 }

 return 0;
}