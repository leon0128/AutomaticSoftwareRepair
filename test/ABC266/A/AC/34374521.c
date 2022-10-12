#include<stdio.h>
#include<string.h>

int main()
{
   int t,mid=0;
   char str1[100];
   gets(str1);

   t=strlen(str1);
   mid = (t+1)/2;
   printf("%c",str1[mid-1]);

    return 0;
}