#include<stdio.h>
#include<string.h>


int main(void)
{
    int a[5];
    int b[101];
    int cnt = 0;
    int i;

    for(i = 0; i < 101; i++)
    {
        b[i] = 0;
    }

    for(i = 0; i < 5; i++)
    {
        scanf("%d",&a[i]);
        b[a[i]]++;
    }
    
    for(i = 0; i < 101; i++)
    {
        if(b[i] != 0)
        {
            cnt++;
        }
    }


    printf("%d",cnt);

    return 0;
}