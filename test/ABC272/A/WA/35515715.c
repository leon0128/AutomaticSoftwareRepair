#include <stdio.h>

int main()
{
    int n, max = -1, i, j, sum, an = 0, bn = 0, x;
    int a[200000];
    int b[200000];

    scanf("%d", &n);
    scanf("%d", &x);
    if(x % 2 == 0) {
        a[0] = x;
        an++;
    } else {
        b[0] = x;
        bn++;
    }
    for(i = 1; i < n; i++) {
       scanf("%d", &x);
        if(x % 2 == 0) {
            for(j = 0; j < an; j++) {
                sum = x + a[j];
                if((sum % 2 == 0) && (max < sum))
                    max = sum;
            }
            a[an] = x;
            an++;
        } else {
            for(j = 0; j < bn; j++) {
                sum = x + b[j];
                if((sum % 2 == 0) && (max < sum))
                    max = sum;
            }
            b[bn] = x;
            bn++;
        }
    }
    printf("%d", max);
}
