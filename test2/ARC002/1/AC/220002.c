#include<stdio.h>

int main(void)
{
	int y=0,result=0;
	// get the input
	scanf("%d",&y);
	
	// Condition
	result = (!(y % 4) && (y % 100)) || !(y % 400);

	printf("%s", result ? "YES\n" : "NO\n");

	return 0;
}