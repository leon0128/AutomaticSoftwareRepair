#include <stdio.h>


int main()
{
    int x,y,n,a,b;
    scanf("%d%d%d",&x,&y,&n);
    a=n/3;

    b=n-a*3;

    printf("%d\n",((a*y)+(b*x)));



    return 0;

}
