#include <stdio.h>
#define N 5

int main(void){
	int count = 0, str[N], judge[N] = {};

	for(int i = 0; i < N; i++){
		scanf("%d", &str[i]);
	}

	for(int i = 0; i < N - 1; i++){
		for(int j = i + 1; j < N; j++){
			if(str[i] == str[j] && judge[j] == 0){
				judge[j]++;
				count++;
			}
		}
	}

	printf("%d\n", N - count);
	return (0);
}