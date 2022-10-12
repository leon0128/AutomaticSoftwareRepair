#include <stdio.h>
int main(void)
{
 	int x,y,n,temp2,temp3,ans1,ans2,ans;
	scanf("%d,%d,%d\n",x,y,n);
  	if(3*x <= y)
    {
		printf("%d\n",n*x);
    }else{
   		temp2 = n/3;
  		temp3 = n%3;
  		ans1 = y*temp2;
        ans2 = temp3*x;
        ans = ans1;ans2;
		printf("%d\n",ans);
    }
  	return 0;
}