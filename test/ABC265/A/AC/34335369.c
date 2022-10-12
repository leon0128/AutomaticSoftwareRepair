#include <stdio.h>
int main()
{
    int x,y;
    int n;
    scanf("%d %d %d",&x,&y,&n);
    int d,v;
    if(3*x<=y)
    {
        printf("%d\n",x*n);
    }
    else
    {
        d=n%3;
        v=n-d;
        v=v/3;
        double p=(y/3);
        printf("%d\n",v*y+d*x);
    }

 return 0;
}
