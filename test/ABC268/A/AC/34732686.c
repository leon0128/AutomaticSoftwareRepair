#include <stdio.h>

int main(){
	int a, b, c, d, e, count;

	count = 1;
	scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
	if (b != a)
		count++;
	if (c != a && c != b)
		count++;
	if (d != a && d != b && d != c)
		count++;
	if (e != a && e != b && e != c && e != d)
		count++;

	printf("%d\n", count);
	return (0);
}