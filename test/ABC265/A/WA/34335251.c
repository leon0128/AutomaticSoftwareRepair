#include <stdio.h>
int main()
{
    double x,y;
    int n;
    scanf("%lld %lld %d",&x,&y,&n);
    int d,v;
    if(x<=(y/3))
    {
        printf("%d\n",x*n);
    }
    else
    {
        d=n%3;
        v=n-d;
        printf("%d\n",v*(y/3)+d*x);
    }

 return 0;
}
