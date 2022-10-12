#include<stdio.h>
/*
	函数： 将十进制数字转换为十六进制，并将转换后的数字存储在字符串中并输出
*/
void dec2hex(int n)
{
	char str[100];
	int p;
	int i;
	int digit;
	char c;
	p = 0;
	do {
		digit = n % 16;
		if (digit < 10)
		{
			str[p] = digit + '0';
		}
		else
		{
			str[p] = digit - 10 + 'A';
		}
		p++;
		n = n / 16;
	} while (n > 0);
	str[p] = '\0';
	for (i = 0; i < p / 2; i++)
	{
		c = str[i];
		str[i] = str[p - 1 - i];
		str[p - 1 - i] = c;
	}
	puts(str);
}

void main()
{
	int n;

	n = 16;
	printf(" \n 十进制数 %d 转化为十六进制 为: ", n);
	dec2hex(n);

	n = 255;
	printf(" \n 十进制数 %d 转化为十六进制 为: ", n);
	dec2hex(n);
}