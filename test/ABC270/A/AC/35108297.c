#include<stdio.h>
#include<string.h>
int main(void) {
	int numA, numB;
	int cnt[3] = {
		0
	};
	int tmp = 0,tmp2 =0;
	scanf("%d%d", &numA, &numB);

	switch (numA)
	{
	case 1:
		cnt[0]++;
		break;
	case 2:
		cnt[1]++;
		break;
	case 3:
		cnt[0]++;
		cnt[1]++;
		break;
	case 4:
		cnt[2]++;
		break;
	case 5:
		cnt[0]++;
		cnt[2]++;
		break;
	case 6:
		cnt[1]++;
		cnt[2]++;
		break;
	case 7:
		cnt[0]++;
		cnt[1]++;
		cnt[2]++;
		break;
	}
	switch (numB)
	{
	case 1:
		cnt[0]++;
		break;
	case 2:
		cnt[1]++;
		break;
	case 3:
		cnt[0]++;
		cnt[1]++;
		break;
	case 4:
		cnt[2]++;
		break;
	case 5:
		cnt[0]++;
		cnt[2]++;
		break;
	case 6:
		cnt[1]++;
		cnt[2]++;
		break;
	case 7:
		cnt[0]++;
		cnt[1]++;
		cnt[2]++;
		break;
	}
	if (cnt[0] == 0 && cnt[1] == 0 && cnt[2] == 0) {
		printf("0");
	}
	else if (cnt[0]>=1 && cnt[1] >= 1 && cnt[2] >= 1) {
		printf("7");
	}
	else if (cnt[0] >= 1 && cnt[1] >= 1) {
		printf("3");
	}
	else if (cnt[0] >= 1 && cnt[2] >= 1) {
		printf("5");
	}
	else if (cnt[1] >= 1 && cnt[2] >= 1) {
		printf("6");
	}
	else if (cnt[0] >= 1) {
		printf("1");
	}
	else if (cnt[1] >= 1) {
		printf("2");
	}
	else if (cnt[2] >= 1) {
		printf("4");
	}


	return 0;
}