#include<stdio.h>
int main()
{
    int x,y,z;
    int ans;
    scanf("%d %d %d",&x,&y,&z);
    if(x>0 && y>0)
    {
        if(y<x && z<0)
        {
            z=-1*z;
          ans = 2*z+x;
          printf("%d",ans);
        }
        else if(y<x && z>0 && z<x)
        {
            ans = x;
            printf("%d",ans);
        }
        else if(y>x)
        {
            ans = x;
            printf("%d",ans);
        }
        else if(z>y)
        {
            printf("-1");
        }
    }else if (x<0 && y<0)
    {
        if(x<y && z>0)
        {  x=-1*x;
          ans = 2*z+x;
          printf("%d",ans);
        }
        else if(x<y && z<0 && z>x)
        {
            ans = -1*x;
            printf("%d",ans);
        }
        else if(y<x)
        {
            ans =-1* x;
            printf("%d",ans);
        }
        else if(z<y)
        {
            printf("-1");
        }
    }

}