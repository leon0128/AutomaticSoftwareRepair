#include <stdio.h>

int main()
{
	int a, b, c, d;

	scanf("%d %d %d %d", &a, &b, &c, &d);

	int res = (a + b) * (c - d);

	printf("%d\n", res);		// 정수 출력
	printf("Takahashi\n");		// 문자열 출력

	return 0;
}
