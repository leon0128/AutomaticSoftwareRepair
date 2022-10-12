#include <stdio.h>



int main() {

	char day[20];

	scanf( "%s", &day );

	switch (day[1]) {
	case 'o': printf("5\n"); break;
	case 'u': printf("4\n"); break;
	case 'e': printf("3\n"); break;
	case 'h': printf("2\n"); break;
	case 'r': printf("1\n"); break;
	}

}