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

	int cnt1 = 0;
	int cnt2 = 0;

	if (y % 4 == 0) { cnt1++; }
	if (y % 100 == 0) { cnt1++; }
	if (y % 400 == 0 || cnt1 == 1) { cnt2++; }

	if (cnt2 == 1) {
		printf("%s\n", "YES");
	}
	else
	{
		printf("%s\n", "NO");
	}

	//getch();
}