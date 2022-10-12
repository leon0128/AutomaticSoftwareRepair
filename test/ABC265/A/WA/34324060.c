#include <stdio.h>

int main() {
    int x, y, n;
    scanf("%d %d %d", &x, &y, &n);
    printf("%d", y*(n / 3) + x*(n % 3));
    
    return 0;
}