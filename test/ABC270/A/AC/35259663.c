#include <stdio.h>

int main()
{
	int A, B;
	int a[3] = { 0 };
	int b[3] = { 0 };
	int c[3];
	int cnt;
	int res;
	int i;

	scanf("%d %d", &A, &B);

	cnt = 0;
	while (A != 0)
	{
		a[cnt] = A % 2;
		A = A / 2;
		cnt++;
	}

	cnt = 0;
	while (B != 0)
	{
		b[cnt] = B % 2;
		B = B / 2;
		cnt++;
	}

	for (i = 0; i < 3; i++)
	{
		if (a[i] == 0 && b[i] == 0)
		{
			c[i] = 0;
		}
		else
		{
			c[i] = 1;
		}
	}

	res = (c[0] * 1) + (c[1] * 2) + (c[2] * 4);

	printf("%d\n", res);

	return 0;
}
