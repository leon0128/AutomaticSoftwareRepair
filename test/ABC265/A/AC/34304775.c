#include <stdio.h>

int main()
{
    int X=0,Y=0,N=0;
    scanf("%d %d %d",&X,&Y,&N);
    int x=X*N,y=(N%3*X)+Y*(N-N%3)/3;
    if(x>=y)
    
    printf("%d\n",y);
    
	else if (x<y)
	
    printf("%d\n",x);
	
    return 0;
}