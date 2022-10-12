#include <stdio.h>



int main(void){
	int x,y,n;
	int ans=0;
	scanf("%d %d %d",&x,&y,&n);
	if(x>(y/3)){
		ans+=(n/3)*y+(n%3)*x;
	}else{
		ans+=n*x;
	}
	printf("%d\n",ans);

	return 0;
}
