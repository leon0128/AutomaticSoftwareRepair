#include<stdio.h>

int main()
{
    int i=0,c=0;
    char s[99];
    scanf("%s",s);
    while(s[i]!='\0')
        {
            i++;
            c++;
        }
    c--;
    c=c/2;
    printf("%c",s[c]);
}