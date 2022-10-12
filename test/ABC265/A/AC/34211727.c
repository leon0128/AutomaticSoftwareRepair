#include<stdio.h>

int main()
{
    int X, Y, N;
    scanf("%d %d %d", &X, &Y, &N);

    int cost = 0;
    while(N>0)
    {
        if(N>=3)
        {
            if(3*X > Y)
            {
                cost += Y;
                N -= 3;
            }
            else
            {
                cost += 3*X;
                N -= 3;
            }
        }
        else
        {
            cost += X;
            N -= 1;
        }
    }

    printf("%d", cost);

    return 0;
}