//AtCoder002-A
#include<stdio.h>

int main(void)
{
	int Y;
	
	if(scanf("%d",&Y) > 2999)
		return -1;
	
    if(Y%4==0 && Y%100==0&&Y%400==0){
        printf("YES\n");
    }
    else if(Y%4==0 && Y%100==0 && Y%400==1){
        printf("NO\n");
    }
    else if(Y%4==1){
        printf("NO\n");
    }
	else{
		printf("NO\n");
	}
	return 0;
}
