#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
    FILE *st;
#else
    #define st stdin
#endif


int n;  

static inline int idx(int i) {
    if (i >= n) {
        return i - n;
    } else if (i < 0) {
        return i + n;
    } else {
        return i;
    }
}

int main() {

#ifdef DEBUG
    st = fopen("./input.txt", "r");
#endif

    int a, b, c, d;
    fscanf(st, "%d%d%d%d", &a, &b, &c, &d);
    printf("%d\nTakahashi\n", (a+b)*(c-d));

#ifdef DEBUG
    fclose(st);
#endif
    return 0;
}
