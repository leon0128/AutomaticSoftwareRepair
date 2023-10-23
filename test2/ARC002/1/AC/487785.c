#include <stdio.h>
int main(void)
{
	int yy;
	scanf("%d",&yy);
	
	if (yy % 400 == 0) {
		printf("YES\n");
	}
	else if (yy % 100 == 0) {
		printf("NO\n");
	}
	else if (yy % 4 == 0) {
		printf("YES\n");
	}
	else {
		printf("NO\n");
	}
	
	return 0;
}
