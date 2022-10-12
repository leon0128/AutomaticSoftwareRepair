#include<stdio.h>
int a,b,c,d,e,ar[110] = {0},sum;
int main()
{
    scanf("%d %d %d %d %d", &a,&b,&c,&d,&e);
    ar[a]=1;
    ar[b]=1;
    ar[c]=1;
    ar[d]=1;
    ar[e]=1;
    for(int i=1;i<=100;i++)
        if (ar[i]==1)
        sum++;
    printf("%d", sum);
}
