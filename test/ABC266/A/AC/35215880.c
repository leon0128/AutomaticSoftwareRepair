#include <stdio.h>
#include <string.h>

int main(void)
{
    int _;
    char s[100];
    _ = scanf("%s", s);
    printf("%c\n", s[(strlen(s)+1)/2-1]);
    return 0;
}