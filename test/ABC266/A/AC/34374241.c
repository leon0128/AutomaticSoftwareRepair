#include <stdio.h>

int main(void)
{
    char s[100];
    scanf("%s", s);
    printf("%c", s[((strlen(s)+1)/2) - 1]);

    return 0;
}