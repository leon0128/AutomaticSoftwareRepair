#include <stdio.h>

int main(void)
{
    int N, a[100];
    int sum = 0;
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%d", &a[i]);
        sum += a[i];
    }
    printf("%d", sum);
    return 0;
}
