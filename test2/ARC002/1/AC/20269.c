#include <stdio.h>

int main(void)
{
     int i; scanf("%d",&i);

     if(i%400==0) puts("YES");
     else if(i%100==0) puts("NO");
     else if(i%4==0) puts("YES");
     else puts("NO");

     return 0;
}
