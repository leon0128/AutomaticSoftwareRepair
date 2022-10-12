#include<stdio.h>
#include<string.h>
int main()
{
    char s[110];
    int i,len;
    scanf("%s",&s);
    len=strlen(s);
    i=len/2;
    printf("%c\n",s[i]);
    return 0;
}
