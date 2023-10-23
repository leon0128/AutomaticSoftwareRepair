#include <stdio.h>
int main()
{
	char *(ans[])={"NO","YES"};
	int Y;
	scanf("%d",&Y);
	puts(ans[((Y%4==0)&&(!(Y%100==0)))||(Y%400==0)]);
	return 0;
}
