#include<stdio.h>


int main()
{
    int X,Y,N;
    scanf("%d %d %d",&X,&Y,&N);

    int first;
    first = X*N;

    int i=3;
    int count = 1;

    while(i<=N)
    {
        i = i + 3;
        count++;
    }
    int I = i-3;
    int Count = count - 1;
    int rem = N - I;
    
    int second = Y * Count + X * rem;

    if(first<second)
    printf("%d",first);
    else
    printf("%d",second);

    return 0;
}