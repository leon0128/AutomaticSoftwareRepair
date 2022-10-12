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

    if (s[0] == 'M')
    {
        printf("%d\n", 5);
    }
    else if (s[0] == 'T' && s[1] == 'u')
    {
        printf("%d\n", 4);
    }
    else if (s[0] == 'W')
    {
        printf("%d\n", 3);
    }
    else if (s[0] == 'T' && s[1] == 'h')
    {
        printf("%d\n", 2);
    }
    else
    {
        printf("%d\n", 1);
    }

    return 0;
}