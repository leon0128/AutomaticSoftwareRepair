#include<stdio.h>

int main()
{
	int a, f, s[5];
	for (f = 0; f < 5; f++)
	{
		scanf("%d", &s[f]);
	}
	for (a = 0; a < 5; a++)
	{
		for (f = 0; f < 4; f++)
		{
			if (s[f] < s[f + 1])
			{
				int b = 0;
				b = s[f];
				s[f] = s[f + 1];
				s[f + 1] = b;
			}
			else
				continue;
		}
	}
	int c = 5;
	for (a = 0; a < 4; a++)
	{
		if (s[a] == s[a + 1])
		{
			c = c - 1;
		}
	}
	printf("%d", c);
}