#include <stdio.h>

int five(int arr[5], int m)
{
	int n,i,b = 0;
	b = arr[0];
	for (i = 0, n = 0; i < 5; i++)
	{
		if (b != arr[i])
		{
			arr[n] = arr[i];
			n++;
		}
		arr[i] = 0;
	}
	switch (n)
	{
	case 0:
		return m;
	
	default :
		five(arr, m + 1);
	}
}
int main()
{
	int a, b, c, d, e = 0;
	scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
	int arr[5] = { a,b,c,d,e };
	if (a == b &&b == c&&c == d &&d== e)
		printf("1");
	else
	printf("%d", five(arr, 0));

	return 0;

}