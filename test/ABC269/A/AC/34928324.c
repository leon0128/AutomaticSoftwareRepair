#include <stdio.h>
#define N 4

int main(void){
	int a[N];
	char str[] = "Takahashi";

	for(int i = 0; i < N; i++){
		scanf("%d", &a[i]);
	}
	printf("%d\n", (a[0] + a[1]) * (a[2] - a[3]));
	printf("%s\n", str);
	return(0);
}