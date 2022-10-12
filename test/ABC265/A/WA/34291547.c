#include <stdio.h>
int main(void)
{
 	int x,y,n,temp1,temp2,temp3,temp4;
	scanf("%d,%d,%d",x,y,n);
  	temp1 = x*n;
  	temp3 = n/y;
  	temp2 = n%3;
  	temp4 = y*temp3+temp2*x;
  	if(3*x < y)
    {
		printf("%d\n",n*x);
    }
  	if(temp1 < temp4)
    {
		printf("%d\n",temp1);
    }else{
		printf("%d\n",temp4);
    }
  	return 0;
}