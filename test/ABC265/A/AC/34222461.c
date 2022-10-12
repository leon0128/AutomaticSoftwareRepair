#include<stdio.h>

int main(void) {
	int R,C,N;
	int num = 0;
	int num2 = 0;
	int cnt = 0;
	int cn = 0;
	scanf("%d%d%d", &R,&C,&N);
	num = R * N;
	num2 = C * (N / 3);
	cn = (N / 3) * 3;
	while (num >= num2 && cn < N)
	{
		num2 += R;
		cn++;
	}
	if (num > num2) {
		printf("%d", num2);
	}
	else {
		printf("%d", num);
	}

	


	return 0;
}