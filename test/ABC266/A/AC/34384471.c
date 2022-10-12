#include<stdio.h>
#include<string.h>

int main(void) {
	char s[100] = {0};
	int leng_s = 0;
	int ans = 0;
	
	scanf("%s", &s);

	leng_s = (int)strlen(s);
	if (leng_s % 2 == 0) {
		ans = (leng_s + 1) / 2;
		printf("%c", s[ans]);
	}
	else {
		ans = leng_s / 2;
		printf("%c", s[ans]);
	}

	return 0;
}