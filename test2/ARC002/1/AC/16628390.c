#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {

	unsigned int	year = 0;
	bool			flg = false;

	scanf("%d", &year);
	if ( (1000 > year) || (year > 2999) ) { return -1; }

	if ( 0 == (year%400) ) {
		flg = true;
	} else if ( 0 == (year%100) ) {
		flg = false;
	} else if ( 0 == (year%4) ) {
		flg = true;
	} else {
		flg = false;
	}

	printf("%s\n", flg ? "YES":"NO");

	return 0;
}