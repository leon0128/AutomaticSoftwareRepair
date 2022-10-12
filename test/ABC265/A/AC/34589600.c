#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
    FILE *st;
#else
    #define st stdin
#endif


int main() {

#ifdef DEBUG
    st = fopen("./input.txt", "r");
#endif
    
    int x, y, n;

    (void) fscanf(st, "%d%d%d", &x, &y, &n);
    
    int q = n / 3;
    int r = n - q * 3;    
    int ans;
    if (y < 3 * x) {
        ans = q * y + r * x;
    } else {
        ans = n * x; 
    }
    printf("%d\n", ans);

#ifdef DEBUG
    fclose(st);
#endif
    return 0;
}
