#include <stdio.h>

int main ()
{
	int a[5], i, j;
	int cnt = 0;
	
	for (i=0; i<5; i++)
	{
		scanf ("%d", &a[i]);
	}
	
	for (i=0; i<4; i++)
	{
		for (j=i+1; j<5; j++)
		if (a[i] == a[j])
		a[j] = j-1000;
	}
	
	for (i=0; i<5; i++)
	{
		if (a[i]>=0)
		{
			cnt++;
		}
	}
	
	printf ("%d", cnt);
	
	return 0;
}