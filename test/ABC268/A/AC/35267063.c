#include <stdio.h>

int main()
{
	int A, B, C, D, E;
	int a[101] = { 0 };
	int cnt = 0;
	int i;

	scanf("%d %d %d %d %d", &A, &B, &C, &D, &E);

	a[A] = 1;
	a[B] = 1;
	a[C] = 1;
	a[D] = 1;
	a[E] = 1;

	for (i = 0; i < 101; i++)
	{
		if (a[i] == 1)
		{
			cnt++;
		}
	}

	printf("%d\n", cnt);

	return 0;
}
