#include <stdio.h>
int main(void)
{
 	int x,y,n,ans;
	scanf("%d,%d,%d\n",x,y,n);
  	if(3*x <= y)
    {
		printf("%d\n",n*x);
    }else{
        ans = y*(n/3) + x*(n%3);
		printf("%d\n",ans);
    }
  	return 0;
}