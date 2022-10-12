#include <stdio.h>

int main(void)
{
    int N;
    scanf("%d", &N);
    if(N == 0)
    {
        printf("00\n");
        return (0);
    }
    else if(1 <= N && N <= 15)
    {
        printf("0");
    }

    char num[3];
    int ex;
    ex = N % 16;
    N = N / 16;

    if(ex <= 9)
        num[0] = '0' + ex;
    else
        num[0] = 'A' + (ex - 10);
    if(N == 0)
        printf("%c\n", num[0]);
    else
    {
        ex = N % 16;
        if(ex <= 9)
            num[1] = '0' + ex;
        else
            num[1] = 'A' + (ex - 10);
        printf("%c%c\n", num[1], num[0]);
    }
    return (0);
}