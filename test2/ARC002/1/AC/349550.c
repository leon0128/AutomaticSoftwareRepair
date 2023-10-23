#include <stdio.h>

int judge(int y){
	if(y%400==0){
		return 1;
	}
	else if(y%100==0){
		return 0;
	}
	else if(y%4==0){
		return 1;
	}
	else{
		return 0;
	}
}

int main(void) {
	int y;
	scanf("%d",&y);
	if(judge(y)==1){
		printf("YES\n");
	}
	else{
		printf("NO\n");
	}
	return 0;
}
