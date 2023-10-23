#include <stdio.h>
int main(){
	int y;
	scanf("%d", &y);
	printf("%s\n",(((y%400==0) ? 1 : (y%100==0) ? 0 : (y%4==0) ? 1 : 0) ? "YES" : "NO"));
	return 0;
}