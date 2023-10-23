//AtCoder002-A
#include<stdio.h>

int main(void)
{
	int Y;
	
	scanf("%d",&Y);
	
	if(Y%4==0&&Y%100==0&&Y%400==0){
		printf("Yes\n");
	}
	else{
		printf("No\n");
	}
	return 0;
}
/*
F:\programing-contest>AtCoder002_A
1001
No

F:\programing-contest>AtCoder002_A
2100
No
*/