#include <stdio.h>
#include <limits.h>

int main(void)
{
    int x, y, n;
    scanf("%d%d%d", &x, &y, &n);
    
    int min = INT_MAX;
    for (int i = 0; i <= n; i++) {
        if ((n - i) % 3 != 0) continue;
        int tmp = ((n - i) / 3) * y + i * x;
        if (tmp < min) min = tmp;
    }
    
    printf("%d", min);
    
    return 0;
}