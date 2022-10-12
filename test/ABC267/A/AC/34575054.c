
#include <stdio.h>
#include <string.h>
int main(void) {
	char x[10];
	char english[5][10] = { "Monday","Tuesday","Wednesday","Thursday","Friday" };
	char chinese[5][10] = { "5","4","3","2","1" };
	int cnt=-1;

	scanf("%s", x);
	do {
		cnt++;
	} while (strcmp(x,english[cnt])!=0);

	printf("%s", chinese[cnt]);
	return 0;

}