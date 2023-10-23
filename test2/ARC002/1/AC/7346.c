#include<stdio.h>

int main(void){
	int Y;
	char *ans = "NO";
	
	scanf("%d", &Y);

	if(Y % 4 == 0){
		ans = "YES";
	}
	
	if(Y % 100 == 0){
		ans = "NO";
	}
	
	if(Y % 400 == 0){
		ans = "YES";
	}

	printf("%s\n", ans);

return 0;
}