#include <stdio.h>

int main() {
	int year, month, day;
	scanf("%d/%d/%d", &year, &month, &day);
	if (year % 400 == 0) {
		printf("YES\n");
	} else if (year % 100 == 0) {
		printf("NO\n");
	} else if (year % 4 == 0) {
		printf("YES\n");
	} else {
		printf("NO\n");
	}
	return 0;
}
