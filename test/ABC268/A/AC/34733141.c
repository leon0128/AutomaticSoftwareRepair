#include<stdio.h>
int main()
{
    int A[5];
    int ans=1;
    for(int i=0;i<5;i++)
    {
        scanf("%d",&A[i]);
    }
    if(A[1]!=A[0])
    {
             ans ++;

    }
    if(A[2]!=A[0] && A[2]!=A[1])
    {
        ans ++;
    }
    if(A[3]!=A[0] && A[3]!=A[1] && A[3]!=A[2])
    {
        ans ++;
    }
    if(A[4]!=A[0] && A[4]!=A[1] && A[4]!=A[2] && A[4]!=A[3])
    {
        ans ++;
    }
    printf("%d",ans);
}