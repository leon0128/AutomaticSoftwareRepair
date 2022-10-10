#include <stdio.h>

int main()
{
    int i,j,N,sum=0;
    scanf("%d",&N);
    for(i=0;i<N;i++)
    {
        scanf("%d",&j);
        sum+=j;
    }
    printf("%d\n",sum);

    return 0;
}
