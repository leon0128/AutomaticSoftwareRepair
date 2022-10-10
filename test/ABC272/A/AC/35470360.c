#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main(void) {
	int N, sum = 0, i = 0;
	int A[101];
	
	scanf("%d", &N);
	for (i = 0; i <= N-1; i++) {
		scanf("%d", &A[i]);
	}
	
	for (i = 0; i <= N-1; i++) {
		sum = sum + A[i];
	}

	printf("%d\n", sum);

	return 0;
}