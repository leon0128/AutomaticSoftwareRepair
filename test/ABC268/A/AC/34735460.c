#include<stdio.h>
#include<string.h>
#include<math.h>
int main()
{
    int a[6],flg=0,ans=0;
    for(int i=1;i<=5;i++)
    {

        scanf("%d",&a[i]);
        flg=1;
        for(int j=i-1;j>0;j--) if(a[i]==a[j]) flg=0;
        ans+=flg;
    }
    printf("%d",ans);
}