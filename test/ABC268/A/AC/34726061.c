#include<stdio.h>
int main()
{
	int a[5], i, n = 5, j, f;
	for (i = 0; i < n; i++)
		scanf("%d", &a[i]);
	int ans = 0;
	for (i = 0; i < n; i++)
	{
		f = 0;
		for (j = 0; j < i; j++)
			if (a[i] == a[j])
				f++;
		if (f == 0)
			ans++;
	}
	printf("%d\n", ans);
	return 0;
}