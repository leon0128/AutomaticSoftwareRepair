#include <stdio.h>

int main()
{
	int day;
	
	scanf("%d", &day);
	
	if(day % 400 == 0) {
		printf("YES\n");
	}
	else {
		if(day % 100 == 0) {
			printf("NO\n");
		}
		else {
			if(day % 4 == 0) {
				printf("YES\n");
			}
			else {
				printf("NO\n");
			}
		}
	}
	
	return 0;
}