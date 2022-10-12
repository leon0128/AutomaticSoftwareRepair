#include <stdio.h>
#include <string.h>
int main()
{
    char s[100];
    scanf("%s", s);
    printf("%c\n", s[(strlen(s) + 1) / 2 - 1]);
    return 0;
}