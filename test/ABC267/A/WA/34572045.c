#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() 
{
	int i=0;
	char in[11];
	int col[8]={};
	scanf("%s",&in);
//	for(i=1;i<8;i++)
//		printf("%c\n",in[i]);
	if(in[0]=='1')
	{
		printf("No\n");
		return 0;
	}

	if(in[6]=='1')
		col[1]=1;
	if(in[3]=='1')
		col[2]=1;
	if(in[7]=='1'||in[1]=='1')
		col[3]=1;
	if(in[4]=='1'||in[0]=='1')
		col[4]=1;
	if(in[8]=='1'||in[2]=='1')
		col[5]=1;
	if(in[5]=='1')
		col[6]=1;
	if(in[9]=='1')
		col[7]=1;
//	for(i=1;i<8;i++)
//		printf("%d\n",col[i]);
	for(i=1;i<6;i++)
		if(col[i]==1)
			if(col[i+1]==0)
				if(col[i+2]==1)
				{
					printf("Yes");
					return 0;
				}
				else
				{
					printf("No");
					return 0;
				}
}

/*
strcpy(p, p1) 复制字符串
strncpy(p, p1, n) 复制指定长度字符串
strcat(p, p1) 附加字符串
strncat(p, p1, n) 附加指定长度字符串
strlen(p) 取字符串长度
strcmp(p, p1) 比较字符串
strcasecmp忽略大小写比较字符串
strncmp(p, p1, n) 比较指定长度字符串
strchr(p, c) 在字符串中查找指定字符
strrchr(p, c) 在字符串中反向查找
strstr(p, p1) 查找字符串
strpbrk(p, p1) 以目标字符串的所有字符作为集合，在当前字符串查找该集合的任一元素
strspn(p, p1) 以目标字符串的所有字符作为集合，在当前字符串查找不属于该集合的任一元素的偏移
strcspn(p, p1) 以目标字符串的所有字符作为集合，在当前字符串查找属于该集合的任一元素的偏移 
* 具有指定长度的字符串处理函数在已处理的字符串之后填补零结尾符 

strtod(p, ppend) 从字符串 p 中转换 double 类型数值，并将后续的字符串指针存储到 ppend 指向的 char* 类型存储。
strtol(p, ppend, base) 从字符串 p 中转换 long 类型整型数值，base 显式设置转换的整型进制，设置为 0 以根据特定格式判断所用进制，0x, 0X 前缀以解释为十六进制格式整型，0    前缀以解释为八进制格式整型
atoi(p) 字符串转换到 int 整型
atof(p) 字符串转换到 double 符点数
atol(p) 字符串转换到 long 整型 

isalpha() 检查是否为字母字符
isupper() 检查是否为大写字母字符
islower() 检查是否为小写字母字符
isdigit() 检查是否为数字
isxdigit() 检查是否为十六进制数字表示的有效字符
isspace() 检查是否为空格类型字符
iscntrl() 检查是否为控制字符
ispunct() 检查是否为标点符号
isalnum() 检查是否为字母和数字
isprint() 检查是否是可打印字符
isgraph() 检查是否是图形字符，等效于 isalnum() | ispunct() */