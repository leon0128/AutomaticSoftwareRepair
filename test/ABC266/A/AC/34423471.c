#include<stdio.h>
#include<string.h>
int main()
{
  char a[101],i;
  gets(a);
  for(i=0;i<strlen(a);i++){
    int z=((0+strlen(a))+1)/2;
    printf("%c",a[z-1]);
    break;
  }
}

