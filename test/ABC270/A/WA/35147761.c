#include<stdio.h>
#include<stdlib.h>

int main(){
	int x,y,z;
	scanf("%d%d%d",&x,&y,&z);
	
	if(y<0){
		x=-x;
		y=-y;
		z=-z;
	}
	
	if(x<y){
		printf("%d\n",abs(x));
	}else{
		if(z>y){
			puts("-1");
		}else{
			printf("%d\n",abs(z)+abs(x-z));
		}
	}
}
