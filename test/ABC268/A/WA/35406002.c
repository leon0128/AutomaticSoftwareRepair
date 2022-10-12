#include<stdio.h>
int main()
{
    int n[5],k;
    scanf("%d %d %d %d %d",&n[0],&n[1],&n[2],&n[3],&n[4]);
    if(n[0]==n[1]&&n[1]==n[2]&&n[2]==n[3]&&n[3]==n[4])
    {
        printf("1"); return 0;
    }
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(n[i]>n[j])
            {
                int y;
                y=n[i];
                n[i]=n[j];
                n[j]=y;
            }
        }
    }
    for(int i=0;i<4;i++)
    {
        if(n[i]!=n[i+1]) k++;
    }
    printf("%d",5-k);
    //printf("%d %d %d %d %d",n[0],n[1],n[2],n[3],n[4]);
    return 0;
}