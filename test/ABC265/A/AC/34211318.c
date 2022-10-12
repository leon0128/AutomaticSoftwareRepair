#include <stdio.h>

int main()
{
    int x, y, n;
    int cost;

    scanf("%d %d %d", &x, &y, &n);
    
    if (x*3 > y)
        cost = (n/3) * y + (n%3) * x;
    else
        cost = (n * x);
    
    printf("%d\n", cost);
    
    return 0;
}