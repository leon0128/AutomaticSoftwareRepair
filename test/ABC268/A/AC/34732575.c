#include <stdio.h>

int main(void) {
    int A[105], X=0, i, t;
    for (i=0; i<=100; i++) {
        A[i]=0;
    }
    for (i=0; i<5; i++) {
        scanf("%d", &t);
        A[t]++;
    }
    for (i=0; i<=100; i++) {
        if (A[i]!=0) X++;
    }
    printf("%d", X);
    return 0;
}
