#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

int main(void){
	int i,j,k,n;
	int count=0;;
	int a,b;
	scanf("%d %d",&a,&b);
	if(a>=4||b>=4){
		count+=4;
		a%=4;
		b%=4;
	}
	if(a>=2||b>=2){
		count+=2;
		a%=2;
		b%=2;
	}
	if(a>=1||b>=1){
		count+=1;
		a%=1;
		b%=1;
	}
	printf("%d",count);

	return 0;
}
