#include <stdio.h>
int main() {
	int x, y, n, a;
	scanf("%d %d %d",&x,&y,&n);
	if (n < 3) a = x*n;
  	else if (y > x*3) a = x*n;
  	else a = y*(n/3)+x*(n%3);
    printf("%d\n",a);
  	return 0;
}