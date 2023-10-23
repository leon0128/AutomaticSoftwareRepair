#include <stdio.h>

int main()
{
	int day;
	
	scanf("%d", &day);
	
	if(day % 400 == 0) {
		printf("Yes\n");
	}
	else {
		if(day % 100 != 0) {
			printf("Yes\n");
		}
		else {
			printf("No\n");
		}
	}
	
	return 0;
}