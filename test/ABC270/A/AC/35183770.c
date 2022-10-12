#include <stdio.h>

int main(void)
{
    int A, B, ans;

    scanf("%d %d", &A, &B);

    ans = A | B;

    printf("%d", ans);

    return 0;
}