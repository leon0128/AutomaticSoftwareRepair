#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
int snum(char s[]) {
	int i;for (i = 0;i < 2000000001;i++)if (s[i] == 0)break;return i;
}


int main()
{
	int n;
	scanf("%d", &n);
	if (n % 400 == 0)
		printf("YES");
	else if (n % 100 == 0)
		printf("NO");
	else if (n % 4 == 0)
		printf("YES");
	else
		printf("NO");
}