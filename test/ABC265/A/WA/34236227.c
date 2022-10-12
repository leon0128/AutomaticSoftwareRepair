#include <stdio.h>

int main(){
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	
	if (a / 3 > b) printf("%d", c / 3 * b);
	else printf("%d", c / 3 * b + a);
	
	return 0;
}