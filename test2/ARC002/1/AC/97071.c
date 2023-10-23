#include <stdio.h>

int main(){
	int y;
	scanf("%d", &y);
	if(y % 400 == 0){ printf("YES\n"); }
	else if(y % 100 == 0){ printf("NO\n"); }
	else if(y % 4 == 0){ printf("YES\n"); }
	else { printf("NO\n"); }
	return 0;
}