#include <stdio.h>
#include <stdlib.h>

int main()
{
char a[100];
int b;
 scanf("%s",&a);

 for(int i=0;;i++)
 {
  if (a[i]=='\0')
  {
     b=i;
    break;
  }
 }
 printf("%c",a[(b+1)/2-1]);
    return 0;
}