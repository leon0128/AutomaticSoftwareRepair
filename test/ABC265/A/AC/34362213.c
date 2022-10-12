#include <stdio.h>

int main (void)
  
{
	int x,y,n,ans;
  	scanf("%d%d%d",&x,&y,&n);
  	if(3*x < y){
    	ans = n * x;
    }else{
    	ans = (n/3) * y;
      	ans = ans + (n%3) * x;
    }
  
  	printf("%d",ans);


}