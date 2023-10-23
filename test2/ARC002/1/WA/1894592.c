/*
AtCoder Regular Contest 002 A - うるう年
Ver1
*/


#include<stdio.h>
#include<stdlib.h>

int main()
{
	int y;
	scanf("%d", &y);
	//printf("%d", y);

	if (y % 4 == 0 || y % 100 != 0 || y % 400 != 0 && y % 4 != 0 || y % 100 == 0 || y % 400 != 0 && y % 4 != 0 || y % 100 != 0 || y % 400 == 0) {
		printf("%s\n", "YES");
	}
	else {
		printf("%s\n", "NO");
	}

	//getch();
}