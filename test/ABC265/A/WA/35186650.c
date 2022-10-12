#include <stdio.h>


int main()
{
    int xx,yy,n,a,b;
    scanf("%d%d%d",&xx,&yy,&n);
    a=n/3;

    b=n-a*3;

    printf("%d\n",((a*yy)+(b*xx)));



    return 0;

}
