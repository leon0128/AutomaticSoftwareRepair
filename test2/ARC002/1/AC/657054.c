#include<stdio.h>

int main(){
	int year;
	scanf("%d", &year);
	
	if (year % 4) {
		printf("NO\n");
		return 0;
	}
	if (!(year % 400)) {
		printf("YES\n");
	} else if (!(year % 100)) {
		printf("NO\n");
	} else {
		printf("YES\n");
	}
	return 0;
}