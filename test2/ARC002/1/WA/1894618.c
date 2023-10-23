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

	if (y % 4 != 0) {
		if (100 != 0) {
			if (400 != 0) {
				printf("%s\n", "NO");
			}
			else {
				printf("%s\n", "YES");
			}
		}
		else {
			printf("%s\n", "YES");
		}
	}
	else {
		printf("%s\n", "YES");
	}
	//getch();
}