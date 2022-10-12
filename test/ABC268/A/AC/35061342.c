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
      
    int ans = 1;
    int a, b, c, d, e;
    (void) fscanf(st, "%d", &a);

    (void) fscanf(st, "%d", &b);
    if (a != b) {
        ans++;
    }

    (void) fscanf(st, "%d", &c);
    if ((c != a) && (c != b)) {
        ans++;
    }

    (void) fscanf(st, "%d", &d);
    if ((d != a) && (d != b) && (d != c)) {
        ans++;
    }

    (void) fscanf(st, "%d", &e);
    if ((e != a) && (e != b) && (e != c) && (e != d)) {
        ans++;
    }

    printf("%d\n", ans);


#ifdef DEBUG
    fclose(st);
#endif
    return 0;
}
