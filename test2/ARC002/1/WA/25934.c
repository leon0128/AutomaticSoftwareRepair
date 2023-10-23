
#include<stdio.h>

int main(void)
{
	int Y;
	
	scanf("%d",&Y);
	
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
