#include <stdio.h>

int main(void)
{
    int n;
    char str[100];

    scanf("%s", str);

    for (n = 0; str[n] != '\0'; ++n);

    printf("%c", str[n / 2]);

    return 0;
}