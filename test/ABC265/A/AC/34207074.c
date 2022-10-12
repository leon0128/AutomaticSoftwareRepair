#include <stdio.h>
int main()
{
    int n,x,y,i,temp,m,a,b;
    scanf("%d%d%d",&x,&y,&n);
    if((x*3)>y)
    {
        if(n%3==0)
        {
            temp=(n/3)*y;
            printf("%d\n",temp);
        }
        else if(n%3!=0)
        {
            temp=(n/3)*y+(n%3)*x;
            printf("%d\n",temp);
        }
    }
    else
    {
        printf("%d\n",n*x);
    }
    return 0;
}