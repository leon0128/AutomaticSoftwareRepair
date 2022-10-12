#include <stdio.h>

int main(void)
{
    char c1, c2;
    scanf("%c%c", &c1, &c2);
    if (c1 == 'M')
        printf("5\n");
    else if (c1 == 'W')
        printf("3\n");
    else if (c1 == 'F')
        printf("1\n");
    else if (c2 == 'u')
        printf("4\n");
    else
        printf("2\n");
    return (0);
}