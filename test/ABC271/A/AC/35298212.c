#include <stdio.h>

int main(void) {
	int n,sum,an;
	scanf("%d", &n);
	sum = n / 16;
	an = n % 16;
	 
	switch (sum) {
	case 10:
		printf("A");
		break;
	case 11:
		printf("B");
		break;
	case 12:
		printf("C");
		break;
	case 13:
		printf("D");
		break;
	case 14:
		printf("E");
		break;
	case 15:
		printf("F");
		break;
	default:
		printf("%d",sum);
		break;
	}
	switch (an) {
	case 10:
		printf("A");
		break;
	case 11:
		printf("B");
		break;
	case 12:
		printf("C");
		break;
	case 13:
		printf("D");
		break;
	case 14:
		printf("E");
		break;
	case 15:
		printf("F");
		break;
	default:
		printf("%d",an);
		break;
	}
	return 0;
}	