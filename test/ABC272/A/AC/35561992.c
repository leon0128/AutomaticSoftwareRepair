#include <stdio.h>
#include <stdlib.h>
int main(void) {
	int n, *arr;
	scanf("%d", &n);
  	arr = (int *) malloc (sizeof(int) * n);
  	int sum = 0;
  	for (int i = 0; i < n; i++) {
    	scanf("%d", &arr[i]);
      	sum = sum + arr[i];
    }
  	printf("%d\n", sum);
}