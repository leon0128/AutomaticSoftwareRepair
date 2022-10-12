#include<stdio.h>

int main()
{
int x[101]={0};
int a,b,c,d,e,cnt=0;
scanf("%d %d %d %d %d",&a,&b,&c,&d,&e);
x[a]=1;
x[b]=1;x[c]=1;x[d]=1;x[e]=1;
for(int i=0;i<101;i++)
{
    if(x[i]!=0)
    {
        cnt++;
    }
}
printf("%d\n",cnt);

return 0;}
