#include<stdio.h>

int main(void) {
	int y;
	scanf("%d",&y);
	if(y%4==0&&y%100!=0){
		puts("YES\n");
		return 0;
	}
	if(y%400==0){
		puts("YES\n");
		return 0;
	}
	printf("NO\n");
	return 0;
}