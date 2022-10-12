#include<stdio.h>
int main()
{
    int x,y,n,a,b,r;
    scanf("%d%d%d",&x,&y,&n);
    if((y/3) >= x)
    {
        r=n*x;
    }
    else if((y/3)<x)
    {
        a=n/3;
        b=n%3;
        r=(a*y+b*x);
    }
    printf("\n%d",r);
    return 0;

}
