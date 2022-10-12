#include<stdio.h>
int main()
{
    int x,y,n;
    scanf("%d %d %d",&x,&y,&n);
    int a=n/3;
    int b=n%3;
    if(x>=y/3)
    {
        printf("%d",(a*y+b*x));
    }
    else
    {
        printf("%d",(n*x));
        }
        return 0;
}
