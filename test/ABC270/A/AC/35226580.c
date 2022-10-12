#include <stdio.h>
#include <string.h>

int main(void)
{

    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);
    int v[3] = {0, 0, 0};

    if (a == 1)
    {
        v[0]++;
    }
    else if (a == 2)
    {
        v[1]++;
    }
    else if (a == 3)
    {
        v[0]++;
        v[1]++;
    }
    else if (a == 4)
    {
        v[2]++;
    }
    else if (a == 5)
    {
        v[0]++;
        v[2]++;
    }
    else if (a == 6)
    {
        v[1]++;
        v[2]++;
    }
    else if (a == 7)
    {
        v[0]++;
        v[1]++;
        v[2]++;
    }

    if (b == 1)
    {
        v[0]++;
    }
    else if (b == 2)
    {
        v[1]++;
    }
    else if (b == 3)
    {
        v[0]++;
        v[1]++;
    }
    else if (b == 4)
    {
        v[2]++;
    }
    else if (b == 5)
    {
        v[0]++;
        v[2]++;
    }
    else if (b == 6)
    {
        v[1]++;
        v[2]++;
    }
    else if (b == 7)
    {
        v[0]++;
        v[1]++;
        v[2]++;
    }

    int ans = 0;
    if (v[0] > 0)
    {
        ans += 1;
    }
    if (v[1] > 0)
    {
        ans += 2;
    }
    if (v[2] > 0)
    {
        ans += 4;
    }

    printf("%d\n", ans);

    return 0;
}