#include<stdio.h>
#include<string.h>
int main(void) {
	int num[5];
	int cnt[5] = {0};
	int c = 0;
	for (int i = 0; i < 5; i++)
	{
		scanf("%d", &num[i]);
		
	}
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = i + 1; j < 5; j++) {
			if (num[i] == num[j]) {
				cnt[i]++;
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (cnt[i] == 0) {
			c++;
		}
	}
	printf("%d", c);
	return 0;
}