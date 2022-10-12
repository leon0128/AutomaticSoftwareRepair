#include <stdio.h>
#include <stdlib.h>
 
int main() {
	int N, Q, L, *a[200001];
	scanf("%d %d", &N, &Q);
  
	for (int i = 0; i < N; i++) {
		scanf("%d", &L);
		a[i] = (int*)malloc(sizeof(int) * (L + 1));
		for (int j = 1; j <= L; j++){
            scanf("%d", &(a[i][j]));
        }
	}
	
	int s, t;
	for (int i = 0; i < Q; i++) {
		scanf("%d %d", &s, &t);
		printf("%d\n", a[s][t]);
	}
	fflush(stdout);
	return 0;
}