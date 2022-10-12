#include<stdio.h>
#include<math.h>
int main()
{
    int a,b,c,d,m,n;
    scanf("%d %d",&a,&b);
    if(a>=4 && b<=3)
    {
        c=a%4;
        d=b%2;
        if(c==3)
        {
            printf("7");
        }
        else if(c==d)
        {
            printf("%d",6+c);
        }
        else if(c==b)
        {
            printf("%d",6+d);
        }
        else printf("%d",6+c+d);
    }
    else if(a<=3 && b>=4)
    {
        m=b%4;
        n=a%2;
        if(m==3)
        {
            printf("7");
        }
        else if(c==d)
        {
            printf("%d",6+c);
        }
        else if(m==n)
        {
            printf("%d",6+n);
        }
        else printf("%d",6+m+n);
    }
    else
        printf("%d",a+b);
    return 0;


}
