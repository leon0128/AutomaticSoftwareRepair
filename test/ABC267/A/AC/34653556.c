#include <stdio.h>

int main(){

	char a[10];
	int ans;
	scanf("%s", &a);
	
	switch(a[1]){
		case 'o':
			ans = 5;
			break;
		case 'u':
			ans = 4;
			break;
		case 'e':
			ans = 3;
			break;
		case 'h':
			ans = 2;
			break;
		default:
			ans = 1;
	}
	
	printf("%d", ans);
	
	return 0;
}