#include <stdio.h>
#include <math.h>
int main()
{
	char a,b;
	a = getchar();
	b = getchar();
	switch (a) {
	case 'M': printf("5"); break;
	case 'W': printf("3"); break;
	case 'F': printf("1"); break;
	case 'T': if (b == 'h') printf("2");
			else if (b == 'u') printf("4"); 
			else printf("input error"); break;
	default: printf("input error"); break;
	}
	return 0;
}
