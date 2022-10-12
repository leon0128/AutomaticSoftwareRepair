#include <stdio.h>
#include <string.h>

int main(void)
{

    char s[100];

    scanf("%s", s);

    int i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    int n = i;

    printf("%c\n", s[(n + 1) / 2 - 1]);

    return 0;
}