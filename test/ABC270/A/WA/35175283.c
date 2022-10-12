#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int A=0, B=0, min=0, max=0, ans=0;
	scanf("%d", &A);
	scanf("%d", &B);

	if (A < B) {
		max = B;
		min = A;
		ans = max + (max - min);
	}
	else
	{
		max = A;
		min = B;
		ans = max + (max - min);
	}

	printf("%d",ans);
	return 0;

}