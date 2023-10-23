#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//A
int main(void){
	int Y;
	scanf("%d", &Y);
	if (Y % 400 == 0){
		printf("YES\n");
		return 0;
	}
	if (Y % 100 == 0){
		printf("NO\n");
		return 0;
	}
	if (Y % 4 == 0){
		printf("YES\n");
		return 0;
	}
	printf("NO\n");
	return 0;
}