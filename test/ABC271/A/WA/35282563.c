#include <stdio.h>

int main(void)
{
    int n;

    scanf("%d", &n);

    unsigned char a[3] = {0};

    a[0] = n / 16;
    a[1] = n % 16;

    for (int i = 0; i < 2; i++)
    {
        if (a[i] <= 9)
        {
            a[i] += 48;
        }
        else
        {
            a[i] += 87;
        }
    }

    printf("%s\n", a);

    return 0;
}