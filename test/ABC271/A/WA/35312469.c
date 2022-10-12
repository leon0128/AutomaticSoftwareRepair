#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
    long *seqStack[1000000];
    unsigned int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        int l;
        scanf("%d", &l);
        long *seq = malloc(l * sizeof(long));
        for (int j = 0; j < l; j++) {
            scanf("%ld", &seq[j]);
        }
        seqStack[i] = seq;
    }

    while(q-- > 0) {
        int s,t;
        scanf("%d %d", &s, &t);
        printf("%ld\n", seqStack[s - 1][t - 1]);
    }

    return 0;
}
