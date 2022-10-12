#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int n,m;
    char str[100];
    char c[2];
    gets(str);
    //printf("%s",str);
    n=strlen(str);
    //printf("%d",n);
    m=(n+1)/2;
    strncpy(c,str+m-1,1);
    printf("%s\n",c);
    return 0;
}
