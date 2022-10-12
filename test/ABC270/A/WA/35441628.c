int main()
{

	int T = 0;
	int A = 0;
	scanf("%d%d", &T, &A);
	int m = T + A;
	if (m == 14)
		m = 13;
	switch (m)
	{
	case 0:
		m = 0;
		printf("%d", m);
		break;
	case 1:
		m = 1;
		printf("%d", m);
		break;
	case 2:
		if (T == 1)
		{
			m = 1;
			printf("%d", m);
		}
		else
		{
			m = 3;
			printf("%d", m);
		}
		break;
	case 4:
	
		if (T == 2)
		{
			m = 2;
			printf("%d", m);
		}
		else
		{
			m = 3;
			printf("%d", m);
		}
		break;
	case 3:
		m = 3;
		printf("%d", m);
		break;
	case 5:
		if (T == 4 || A == 4)
		{
			m = 5;
			printf("%d", m);
		}
		else
		{
			m = 3;
			printf("%d", m);
		}
		break;
	case 6:
		if (T == 1 || A == 1)
		{
			m = 5;
			printf("%d", m);
		}
		if (T == 3)
		{
			m = 3;
			printf("%d", m);
		}
		else
		{
			m = 6;
			printf("%d", m);
		}
		break;
	case 7:
		if (T == 2 || A == 2)
		{
			m = 5;
			printf("%d", m);
		}
		else
		{
			m = 7;
			printf("%d", m);
		}
		break;
	case 8:
		if (T == 4)
		{
			m = 4;
			printf("%d", m);

		}
		if (T == 2 || A == 2)
		{
			m = 6;
			printf("%d", m);
		}
		else
		{
			m = 7;
			printf("%d", m);
		}
		break;
	case 9:
		if (T == 4 || A == 4)
		{
			m = 5;
			printf("%d", m);
		}
		else
		{
			m = 7;
			printf("%d", m);
		}
		break;
	case 10:
		if (T == 4 || A == 4)
		{
			m = 6;
			printf("%d", m);
		}
		if (T == 5)
		{
			m = 5;
			printf("%d", m);
		}
		else
		{
			m = 7;
			printf("%d", m);
		}
		break;
	case 11:
		m = 7;
		printf("%d", m);
		break;
	case 12:
		if (T == 6)
		{
			m = 6;
			printf("%d", m);
		}
		else
		{
			m = 7;
			printf("%d", m);
		}
		break;
	case 13:
		m = 7;
		printf("%d", m);
	}
	return 0;
	}
