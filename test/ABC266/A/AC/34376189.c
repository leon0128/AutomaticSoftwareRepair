#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[100];
    scanf("%s", &s);

    size_t len;
    len = strlen(s);

    printf("%c\n", s[(len + 1) / 2 - 1]);

    return 0;
}
