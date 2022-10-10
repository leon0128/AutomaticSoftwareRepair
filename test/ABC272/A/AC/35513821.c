#include <stdio.h>

int main() {
  	int n, m, sum=0, i;
  
    scanf("%d", &n);
  	for(i = 0; i < n; i++) {
        scanf("%d", &m);
        sum += m;
    }
  	printf("%d", sum);
}