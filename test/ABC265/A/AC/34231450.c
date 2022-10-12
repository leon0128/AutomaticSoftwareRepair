#include<stdio.h>
int main()
{
    int x,y,n,a,b,c;
    scanf("%d%d%d",&x,&y,&n);
    if(x==y)
    {
        a=n/3;
        b=n%3;
        int s=a*y+b*x;
        printf("%d\n",s);
    }
    else if(x<y/3)
    {
       printf("%d\n",n*x);
    }
    else if(x>y/3)
    {
        a=n/3;
        b=n%3;
        int s=a*y+b*x;
        printf("%d\n",s);
    }
    return 0;
}
