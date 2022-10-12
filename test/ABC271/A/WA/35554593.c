#include <stdio.h>
#include<stdlib.h>
#include<math.h>

int main() {
	int N, Q;
	int* L;
	int i, j, index_input, index_query;
	int* a;
	int s, t;
	int* output;

	a = (int*)malloc(sizeof(int) * 2 * (int)pow(10, 5));
	scanf("%d %d", &N, &Q);
	L = (int*)malloc(sizeof(int) * N);
	output = (int*)malloc(sizeof(int) * Q);

	//数列の入力
	for (i = 0; i < N; i++) {
		scanf("%d", &L[i]);
		index_input = 0;
		for (j = 0; j < i; j++) {
			index_input += L[j];
		}
		for (j = 0; j < L[i]; j++) {
			scanf("%d", &a[index_input+j]);
		}
	}

	//クエリの入力
	for (i = 0; i < Q; i++) {
		scanf("%d %d", &s, &t);
		index_query = 0;
		for (j = 0; j < (s - 1); j++) {
			index_query += L[j];
		}
		output[i] = index_query + (t - 1);
	}

	for (i = 0; i < Q; i++) {
		printf("%d\n", a[output[i]]);
	}

	free(a);
	free(L);
	free(output);
	return 0;
}