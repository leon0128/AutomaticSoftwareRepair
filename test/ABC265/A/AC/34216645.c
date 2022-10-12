#include<stdio.h>
int main(void)
{
    int x,y;
    int N;
    int ans;
    scanf("%d %d %d",&x,&y,&N);
    int total=x*N;
    if(x<=(y/3))
        ans=x*N;
    else if(3*x>y) 
        ans=(x*(N%3))+(y*(N/3));
    printf("%d",ans);
    return 0;
}