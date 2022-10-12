#include <stdlib.h>

int main(void) {
    int x, y, n;
    int z;
    scanf("%d %d %d", &x, &y, &n);
    if(3 * x <= y) {
        z = n * x;
        printf("%d\n", z);
    } else {
        int k = n / 3;
        int l = n % 3;
        z = y * k + x * l;
        printf("%d\n", z);
    }
    return 0;
}