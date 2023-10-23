#include <stdio.h>

int main()
{
	int year, uru = 0;
	scanf("%d", &year);
	if(year < 1000 || year > 3000){
		return 1;
	}
	if( year % 4 == 0 ){
		uru = 1;
	}
	if( year % 400 != 0 && year % 100 == 0){
		uru = 0;
	}

	if( uru == 1 )
		printf("YES\n");
	else
		printf("NO\n");

	return 0;
}
