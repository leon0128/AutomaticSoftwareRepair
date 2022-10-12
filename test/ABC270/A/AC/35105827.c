#include <stdio.h>

int main(void)
{
    int A;
    int B;
    scanf("%d %d", &A, &B);

    int C[3] = {0, 0, 0};
    if (A == 1 || A == 3 || A == 5 || A == 7)
        C[0]++;
    if (A == 2 || A == 3 || A == 6 || A == 7)
        C[1]++;
    if (A == 4 || A == 5 || A == 6 || A == 7)
        C[2]++;
    
    if (B == 1 || B == 3 || B == 5 || B == 7)
        C[0]++;
    if (B == 2 || B == 3 || B == 6 || B == 7)
        C[1]++;
    if (B == 4 || B == 5 || B == 6 || B == 7)
        C[2]++;
    
    int ans = 0;
    if (C[0] >= 1)
        ans = ans + 1;
    if (C[1] >= 1)
        ans = ans + 2;
    if (C[2] >= 1)
        ans = ans + 4;
    
    printf("%d\n", ans);
    return (0);
}