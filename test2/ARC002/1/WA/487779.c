#include <stdio.h>
int main(void)
{
	int yy;
	scanf("%d",&yy);
	
	if (yy % 400 == 0) {
		printf("うるう年\n");
	}
	else if (yy % 100 == 0) {
		printf("うるう年ではない\n");
	}
	else if (yy % 4 == 0) {
		printf("うるう年\n");
	}
	else {
		printf("うるう年ではない\n");
	}
	
	return 0;
}
