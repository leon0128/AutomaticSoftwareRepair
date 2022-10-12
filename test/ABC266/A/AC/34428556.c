#include<stdio.h>
#include<string.h>
int main()
{
    char s[105];
    gets(s);
    int k = strlen(s);
    k=k/2;
    printf("%c\n", s[k]);
    return 0;
}
