#include<stdio.h>
int main() {
	int y, cnt = 0;
	scanf("%d", &y);
	if (y % 4 == 0) cnt = 1;
	if (y % 100 == 0) cnt = 0;
	if (y % 400 == 0) cnt = 1;
	if (cnt == 1) printf("YES");
	else printf("NO");
	return 0;
}