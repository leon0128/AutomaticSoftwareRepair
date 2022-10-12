#include <stdio.h>
#include <string.h>
#include <math.h>

int main() {
	char s[100];
	int l;
	int m;

	//scanf_s("%s", s, 100);
	scanf("%s", s);

	l = strlen(s);//sの長さ
	m = ceil((l + 1) / 2);//sの真ん中が前から何番目か
	printf("%c", s[m - 1]);
}