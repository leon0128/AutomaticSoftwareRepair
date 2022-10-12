#include<stdio.h>
#include<string.h>
int main(void) {
	char str[5][50] = { {"Monday"},{"Tuesday"},{"Wednesday"},{"Thursday"},{"Friday "} };
	char s[50];
	scanf("%s", s);

	
	switch (s[0])
	{
	case 'M':
		printf("5");
		break;
	case 'T':
		if (s[1] == 'u') {
			printf("4");
		}
		else {
			printf("2");
		}
		break;
	case 'W':
		printf("3");
	break; 
	case 'F':
		printf("1");
		break;
	}

	return 0;
}