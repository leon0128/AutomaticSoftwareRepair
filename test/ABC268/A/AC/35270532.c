#include <stdio.h>

int main() {
    int A, B, C, D, E;
    int N[101] = {0};
    int res = 0;

    scanf("%d %d %d %d %d", &A, &B, &C, &D, &E);

    ++N[A];
    ++N[B];
    ++N[C];
    ++N[D];
    ++N[E];

    for(int i = 0; i < 101; ++i) {
        if (N[i] != 0) {
            ++res;
        }
    }

    printf("%d\n", res);
    return(0);
}