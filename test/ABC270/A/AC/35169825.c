#include <stdio.h>

int main() {

	int A, B, S = 0;

	scanf("%d", &A);
	scanf("%d", &B);

	S = A | B;
	printf("%d\n", S);
	
	return 0;
}