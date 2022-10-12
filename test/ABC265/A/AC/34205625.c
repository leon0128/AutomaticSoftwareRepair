#include <stdio.h>
int main(void)
{
	int x, y, n, res;

	scanf("%d %d %d", &x, &y, &n);

	if (y<3*x) {
      	res=y*(n/3)+x*(n%3);
    }
  	else {
      	res=x*n;
    }

	printf("%d", res);

	return 0;
}