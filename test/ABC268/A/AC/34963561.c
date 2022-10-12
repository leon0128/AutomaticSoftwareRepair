#include <stdio.h>
#include <string.h>

int main(void)
{

    int a[5];

    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (a[i] > a[j])
            {
                int x = a[i];
                a[i] = a[j];
                a[j] = x;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < 4; i++)
    {
        if (a[i] != a[i + 1])
        {
            ans++;
        }
    }

    printf("%d\n", ans + 1);

    return 0;
}