#include<stdio.h>
int main()
{
//1 0  2 1  4 2
    int n,m,ans=0;
    int a[2]={0,0,0};
    scanf("%d %d",&n,&m);
    if(n==1 || m==1)
    {
        a[0]=1;
    }
    if(n==2 || m==2)
    {
        a[1]=1;
    }
    if(n==3 || m==3)
    {
        a[1]=1; a[0]=1;
    }
    if(n==4 || m==4)
    {
        a[2]=1;
    }
    if(n==5 || m==5)
    {
        a[2]=1; a[0]=1;
    }
    if(n==6 || m==6)
    {
        a[2]=1; a[1]=1;
    }
    if(n==7 || m==7)
    {
        a[2]=1; a[1]=1; a[0]=1;
    }

    if(a[0]==1) ans+=1;
    if(a[1]==1) ans+=2;
    if(a[2]==1) ans+=4;
    printf("%d",ans);
    return 0;
}