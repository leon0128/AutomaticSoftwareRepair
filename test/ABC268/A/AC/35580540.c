#include <stdio.h>
int main()
{
	int a[5], i, j, n = 5;
	for (i = 0; i < 5; i++)
	{
		scanf("%d", &a[i]);
		for (j = 0; j < i; j++)
		{
			if (a[i] == a[j])
			{
				n--;
				break;
			}
			
		}
	}
	printf("%d\n", n);
	return 0;
}