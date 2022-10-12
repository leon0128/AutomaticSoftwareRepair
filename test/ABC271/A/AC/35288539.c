#include<stdio.h>
#include<stdlib.h>
int main()
{
	int num,n,i=0,re=0,j;
	char a[100]={0};
	scanf("%d",&num);
	n = 16;
	if(num == 0){
		printf("00");
		return 0;
	}
	while(num!=0)
	{
		re=num%n;
		if(re<=9&&re>=0)
		{
			a[i]=re+'0';
		}
		else if(re<=16&&re>=10)
		{
			a[i]=re-10+65;
		}
		i=i+1;
		num=num/n;
	}
	if(i-1 == 0){
	printf("0");}
	for(j=i-1;j>=0;j--)
	{
		printf("%c",a[j]);
	}
	return 0;
}