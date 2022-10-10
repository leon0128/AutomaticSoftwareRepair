#include<stdio.h>
#include<string.h>
int main()
{
	int n = 0;
	int result = 0;
	int arr[] = { 0 };
	memset(arr, 0,sizeof(arr) );
	scanf("%d", &n);
	for (int i = 0; i <= n-1; i++)
	{
		scanf("%d", &n);
		arr[i] = n;
		result = arr[i] + arr[i + 1];
	}
	
	printf("%d\n", result);
	return 0;
}
