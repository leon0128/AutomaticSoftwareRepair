#include<stdio.h>


int main() {
	int n, sum,i,c;
	sum = 0;
	scanf("%d",&n);
	for (i = 1; i < n + 1; i++) {
		scanf("%d", &c);
		sum = sum + c;
	}
	printf("%d",sum);
	return 0;
}