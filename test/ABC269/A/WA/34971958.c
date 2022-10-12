#include <stdio.h>

int main(void)
{
    char s[10][10];
    int a, b, c, d;
    int out = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            scanf("%c", &s[i][j]);
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (s[i][j] != s[i][j + 1])
            {
                a = i;
                c = j + 1;
                out = 1;
            }

            break;
        }
        if (out == 1)
        {
            break;
        }
    }
    out = 0;

    for (int i = 10; i >= 0; i--)
    {
        for (int j = 10; j > 0; j--)
        {
            if (s[i][j] != s[i][j - 1])
            {
                b = i;
                d = j;
                out = 1;
            }
            break;
        }
        if (out == 1)
        {
            break;
        }
    }

    printf("%d %d\n", a, b);
    printf("%d %d\n", c, d);

    return 0;
}