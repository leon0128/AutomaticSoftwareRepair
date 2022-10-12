#include<stdio.h>
#include<string.h>
int main(void) {
	int num[5];
	int cnt = 0;
	for (int i = 0; i < 5; i++)
	{
		scanf("%d", &num[i]);
		for (int j = 0; j < i; j++)
		{
			if (num[i] != num[j]) {
				cnt++;
			}

		}
	}
	if (cnt % 5 == 0) {
		printf("1");
	}else{
		printf("%d", cnt % 5);

	}

	return 0;
}