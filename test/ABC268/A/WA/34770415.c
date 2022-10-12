#include <stdio.h>
#define N 102
 
int main(void){
	int x, ans, num[N] = {};

	for(int i = 0; i < 5; i++){
		scanf("%d", &x);
		num[x]++;
	}

	for(int i = 0; i < N; i++){
		if(0 < num[i]){
			ans++;
		}
	}

	printf("%d\n", ans);
	return (0);
}