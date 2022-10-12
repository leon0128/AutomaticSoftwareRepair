#include<stdio.h>
#include<string.h>
int main()
{
    char s[99];
    scanf("%s",s);
    int n;
    n=strlen(s)/2;
    printf("\n%c",s[n]);
    return 0;
}
