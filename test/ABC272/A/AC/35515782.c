#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);

    int x, Integer_Sum = 0;

    while(n--)
    {
        scanf("%d", &x);
        Integer_Sum = Integer_Sum + x;
    }

    printf("%d", Integer_Sum);

    return 0;
}