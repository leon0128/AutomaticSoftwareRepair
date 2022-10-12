#include <stdio.h>
int main(void) {
	int i = 0;
	char S[10];
	scanf("%s", S);

	if (S[0] == 'M')printf("5");
	if (S[0] == 'T'&&S[1]=='u')printf("4");
	if (S[0] == 'W')printf("3");
	if (S[0] == 'T' && S[1] == 'h')printf("2");
	if (S[0] == 'F' )printf("1");

	return 0;

}