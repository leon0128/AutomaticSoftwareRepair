#include <stdio.h>
int main(void) {
	int i = 0;
	char S[10];
	char day1[10] = "monday";
	char day2[10] = "tuesday";
	char day3[10] = "wednesday";
	char day4[10] = "thuesday";
	char day5[10] = "friday";
	scanf("%s", S);

	while (S[i] != '\0' && day1[i] != '\0')
		if (S[i] != day1[i]) break;
		else printf("5");
	while (S[i] != '\0' && day2[i] != '\0')
		if (S[i] != day2[i]) break;
		else printf("4");
	while (S[i] != '\0' && day3[i] != '\0')
		if (S[i] != day3[i]) break;
		else printf("3");
	while (S[i] != '\0' && day4[i] != '\0')
		if (S[i] != day4[i]) break;
		else printf("2");
	while (S[i] != '\0' && day5[i] != '\0')
		if (S[i] != day5[i]) break;
		else printf("1");

	return 0;

}