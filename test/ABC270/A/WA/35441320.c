int main()
{

	int T = 0;
	int A = 0;
	scanf("%d%d", &T, &A);
	int m = T + A;
	if (m >= 7)
		m = 7;
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
		m = 3;
		printf("%d", m);
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
		else
		{
			m = 6;
			printf("%d", m);
		}
		break;
	case 7:
		m = 7;
		printf("%d", m);
		break;
	}





	return 0;
}