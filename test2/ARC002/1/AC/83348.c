#include<stdio.h>

int ifuru(y){
	if(y%400==0){
		return 1;
	}else if(y%100==0){
		return 0;
	}else if(y%4==0){
		return 1;
	}else{
		return 0;
	}
}
int main(y){
	scanf("%d",&y);
	if(ifuru(y)==1){
		printf("YES\n");
	}else{
		printf("NO\n");
	}
	return 0;
}