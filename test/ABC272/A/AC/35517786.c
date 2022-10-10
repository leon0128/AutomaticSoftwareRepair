#include <stdio.h>

int main()
{
    int arr[100], N, sum=0, i, j;
    scanf("%d",&N);

    for (i = 0; i < N; ++i)
    {
        scanf("%d",&arr[i]);
        sum = sum + arr[i];
           }
     printf("%d", sum);
     return 0;
}