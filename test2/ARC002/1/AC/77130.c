#include<stdio.h>

int main(void) {
	int year;
	
	scanf("%d", &year);
	
	if(year % 400 == 0) {
		puts("YES");
	}else if (year % 100 == 0) {
		puts("NO");
	}else if (year % 4 == 0) {
		puts("YES");
	}else {
		puts("NO");
	}

	return 0;
}
