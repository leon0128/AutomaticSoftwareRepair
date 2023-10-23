// AtCoder ARC002: A - うるう年
// 2019.8.26 bal4u

#include <stdio.h>

int main()
{
	int Y;
	
	scanf("%d", &Y);
	puts((Y%4 == 0 && Y%100 != 0 || Y%400 == 0)? "YES": "NO");
	return 0;
}
