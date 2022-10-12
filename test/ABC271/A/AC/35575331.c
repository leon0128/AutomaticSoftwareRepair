#include <stdio.h>

int main(void){
	int in,temp[2];
	char roma[17] = "0123456789ABCDEF";
	char ans[2];
	
	scanf("%d", &in);
	
	temp[0] = in / 16;
	temp[1] = in % 16;
	
	ans[0] = roma[ temp[0] ];
	ans[1] = roma[ temp[1] ];
	
	printf("%c%c", ans[0], ans[1]);
	return 0;
}