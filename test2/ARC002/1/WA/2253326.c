#include <stdio.h>
#include <math.h>
#include <string.h>
int main(){
	int y;
	scanf("%d",&y);
	if(y%100==0&&y%400==0||y%4==0)
		printf("YES\n");
	else
		printf("NO\n");
	return 0;
}