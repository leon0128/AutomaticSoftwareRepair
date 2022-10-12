#include<stdio.h>
#include<string.h>
int main()
{
	char s[100];
	char a[100] ="Monday";
	char b[100] = "Tuesday";
	char c[100] = "Wednesday";
	char d[100] = "Thursday";
	char e[100] = "Friday";
	scanf("%s", &s);
	if (strcmp(s, a) == 0)
		printf("%d", 5);
	else if (strcmp(s, b) == 0)
		printf("%d", 4);
	else if (strcmp(s, c) == 0)
		printf("%d", 3);
	else if (strcmp(s, d) == 0)
		printf("%d", 2);
	else if (strcmp(s, e) == 0)
		printf("%d", 1);
	else
		printf("语法错误，请重新输入！！");		
		
		
	return 0;
}