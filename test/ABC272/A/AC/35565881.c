#include<stdio.h>
int main()
{
    int t;
    scanf("%d",&t);
    int x=0;
    while(t--)
    {
        int a;
        scanf("%d",&a);
        x+=a;
    }
    printf("%d",x);
    return 0;
}
