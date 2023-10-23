#include <stdio.h>

int main()
{
	int year;
	
	int uruu = 0; /* 閏年なら1,違うなら0。初期値は規則4に同じ*/
	
	scanf("%d",&year);
	
	if (!(year % 4)) { /* 規則1 */
		uruu = 1;
	}
	if (!(year % 100)) {/* 規則2 */
		uruu = 0;
	}
	if (!(year % 400)) {/* 規則3 */
		uruu = 1;
	}
	
	if (uruu) {
		printf("YES\n");
	}
	else {
		printf("NO\n");
	}
	
	return 0;
}