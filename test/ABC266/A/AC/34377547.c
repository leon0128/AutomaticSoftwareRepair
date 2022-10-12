#include<stdio.h>
#include<string.h>
int main()

{
    char s[100];
    int i,j,k;

    gets(s);
    i=strlen(s);
    k=(i+1)/2;

     printf("%c",s[k-1]);
     return 0;


}
