#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
int main()
{
    int length;
    char s[100];
    int a;
    scanf("%s", s);
    length=strlen(s);
    a=length/2;
    printf("%c", s[a]);
    return 0;
}