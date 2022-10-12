#include<stdio.h>
int main()
{
    char s[100];
    gets(s);
    int len=strlen(s);
    if(len%2==0)
    {
        printf("%c",s[len/2-1]);
    }
    else {
        printf("%c",s[len/2]);
    }
}
