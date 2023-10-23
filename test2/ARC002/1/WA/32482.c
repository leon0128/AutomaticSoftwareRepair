#include <stdio.h>

int main(){
	int y;
	scanf("%d", &y);
	printf(y % 4 == 0 ? (y % 100 == 0 ? (y % 400 == 0 ? "YES\n" : "NO\n") : "YES\n") : "\nNO");
	return 0;
}