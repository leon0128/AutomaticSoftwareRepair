#include <stdio.h>

int main(void)
{
    int x, y, n;
    scanf("%d%d%d", &x, &y, &n);
    
    int min = 1 << 10;
    for (int i = 0; i <= n; i++) {
        if ((n - i) % 3 != 0) continue;
        int tmp = ((n - i) / 3) * y + i * x;
        if (tmp < min) min = tmp;
    }
    
    printf("%d", min);
    
    return 0;
}