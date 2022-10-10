#include<stdio.h>
int main() {
	int a;
	scanf("%d", &a);
	int sum =0, n;
	for(int i=0; i<a; i++) {
		scanf("%d", &n);
		sum = sum+n;
	}
	printf("%d\n", sum);
	return 0;
}