#include <stdio.h>

int main ( void ){
	int n;
	scanf("%d",&n);
	int sum = 0;
	int a[n];
	for(int i = 0; i < n; i++){
		scanf("%d",&a[i]);
		sum = sum + a[i];
	}
	printf("%d",sum);
	return 0;
}