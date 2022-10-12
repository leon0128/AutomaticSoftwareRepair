#include <stdio.h>
int main(void)
{
	int X,Y,N ;
	scanf("%d %d %d", &X,&Y,&N);
	if (Y/3<=X/1) {
		printf("%d",(Y*(N/3))+(X*(N%3)));
		}
	else {
		printf("%d", X * N);
	}
	return 0;
}