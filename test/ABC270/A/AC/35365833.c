#include<stdio.h>
int main() {
	int A, B,num;
	scanf("%d", &A);
	scanf("%d", &B);
	if (0<=A&&A<=7&&0<=B&&B<=7) {
		num = A | B;
		printf("%d", num);
	}
		return 0;
	
}
