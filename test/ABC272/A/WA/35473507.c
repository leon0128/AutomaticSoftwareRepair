#include<stdio.h>


int main() {
	int n, sum;
	scanf("%d",&n);
	int i,c;
	for (i = 1; i < n + 1; i++) {
		scanf("%d", &c);
		sum = sum + c;
	}
	printf("%d",sum);
	return 0;
}