#include <stdio.h>

int main(){
	int Y, res = 0;
	scanf("%d", &Y);
	if(Y % 4 == 0) res = ~res;
	if(Y % 100 == 0) res = ~res;
	if(Y % 400 == 0) res = ~res;

	printf("%s\n", res?"YES":"NO");
	return 0;
}