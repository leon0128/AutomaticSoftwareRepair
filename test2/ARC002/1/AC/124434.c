#include <stdio.h>

int main(void) {
	const char *p;
	unsigned short year;
	const char YES[] = "YES";
	const char NO[] = "NO";
	
	scanf("%hd", &year);
	
	p = &NO[0];
	if (year % 400 == 0) 
		p = &YES[0];
	else if (year % 100 == 0) 
		p = &NO[0];
	else if (year % 4 == 0)
		p = &YES[0];
	
	printf("%s\n", p);

	return 0;
}