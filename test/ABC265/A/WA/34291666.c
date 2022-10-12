#include <stdio.h>
int main(void)
{
 	int x,y,n,temp2,temp3,temp4;
	scanf("%d,%d,%d",x,y,n);
  	if(3*x < y)
    {
		printf("%d\n",n*x);
    }else{
   		temp3 = n/y;
  		temp2 = n%3;
  		temp4 = y*temp3+temp2*x;
		printf("%d\n",temp4);
    }
  	return 0;
}