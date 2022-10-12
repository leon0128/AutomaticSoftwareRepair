#include<stdio.h>
#include<string.h>


int main(void)
{
    int a[4];
    int i;

    for(i = 0; i < 4; i++)
    {
        scanf("%d",&a[i]);
    }

    int res = (a[0] + a[1]) * (a[2] - a[3]);


    printf("%d\n",res);
    printf("Takahashi\n");

    return 0;
}