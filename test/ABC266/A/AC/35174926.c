#include<stdio.h>
#include<string.h>

int main()
{
    char s[100];
    gets(s);
    int a;
    a=strlen(s);
    
    printf("%c",s[a/2]);
    
    return 0;
}