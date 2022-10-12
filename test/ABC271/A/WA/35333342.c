#define  _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
char  buffer[33];
char* inttohex(int  aa)
{
	sprintf(buffer, "%x", aa);
	return  (buffer);
}
int main()
{
	int  num;
	char* hex_str;
	printf("Enter a number: ");
	scanf("%d", &num);
	hex_str = inttohex(num);
	printf("Hexadecimal number: %sH\n", hex_str);

	return 0;
}