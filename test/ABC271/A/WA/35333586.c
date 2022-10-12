#define  _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	char a[40] = { "0123456789ABCDEF" };//用一个数组存储十六进制数
	char b[100] = {0};
	int n=0;
	int cnt=0;//计数

	scanf("%d", &n);//输入要转换的十进制数

	if (n == 0)
		printf("0");
	while (n != 0)
	{
		b[++cnt] = a[n % 16];//这里cnt从1开始
		n = n / 16;
	}

	for (int i = cnt; i > 0; i--)/*上面cnt从1开始所以i>0，不用输出b[0]。逆序输出*/
		printf("%c", b[i]);

	return 0;
}