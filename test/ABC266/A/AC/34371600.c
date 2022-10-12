#include<stdio.h>
#include<string.h>

int main()
{


    char s[100];
    scanf("%s", s);

    printf("%c", (s[(strlen(s))/2]));

    return 0;
}