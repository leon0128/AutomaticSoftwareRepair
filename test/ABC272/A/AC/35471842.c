#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    int integer = 0;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &integer);
        sum = sum + integer;
    }
    printf("%d",sum);
}