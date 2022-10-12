#include<stdio.h>
int main()
{
	int a, b, c;
	int x[4] = { 0,0,0,0 };
	int y[4] = { 0,0,0,0 };
	int z[4] = { 0,0,0,0 };
	scanf("%d %d", &a, &b);
	switch (a)
	{
	case 0:; break;
	case 1: x[0] = 1; break;
	case 2: x[1] = 2; break;
	case 3: x[0] = 1; x[1] = 2; break;
	case 5: x[0] = 1; x[3] = 4; break;
	case 6: x[1] = 2; x[3] = 4; break;
	case 7: x[1] = 1; x[3] = 4; x[2] = 2; break;
	}

		switch (b)
		{
		case 0:; break;
		case 1: y[0] = 1; break;
		case 2: y[1] = 2; break;
		case 3: y[0] = 1; y[1] = 2; break;
		case 5: y[0] = 1; y[3] = 4; break;
		case 6: y[1] = 2; y[3] = 4; break;
		case 7: y[1] = 1; y[3] = 4; y[2] = 2; break;
		}
		for (int i = 0; i <= 3; i++)
		{
		
			if (x[i] - y[i] >0)
			{
				z[i] = x[i];
			}
			else if (x[i] - y[i] < 0)
			{
				z[i] = y[i];
			}
			else if (x[i] - y[i] == 0)
			{
				z[i] = x[i];
			}
		}
		c = z[1] + z[2] + z[3];
		printf("%d", c);
	return 0;
}