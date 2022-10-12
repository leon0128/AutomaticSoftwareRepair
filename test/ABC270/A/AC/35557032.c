#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
FILE *st;
#else
#define st stdin
#endif

int main() {

#ifdef DEBUG
    st = fopen("./input.txt", "r");
#endif

    int a, b;
    fscanf(st, "%d%d", &a, &b);
    printf("%d\n", a | b);

#ifdef DEBUG
    fclose(st);
#endif
    return 0;
}
