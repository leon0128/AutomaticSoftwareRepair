#include<stdio.h>
int a[102];
int main()
{
	int n;
	scanf("%d", &n);
	int i;
	for (i = 0; i < n; i++)
		scanf("%d", &a[i]);
	int sum = 0;
	for (i = 0; i < n; i++)
		sum += a[i];
	printf("%d\n", sum);
	return 0;
}