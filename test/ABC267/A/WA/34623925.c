#include<stdio.h>
int main()
{
    char s[100];
    gets(s);
    if(s[100]=='Monday')
        printf("5");
    else if(s[100]=='Tuesday')
        printf("4");
     else if(s[100]=='Wednesday')
      printf("3");
     else if(s[100]=='Thursday')
        printf("2");
     else
        printf("1");
     return 0;
}