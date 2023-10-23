#include<stdio.h>

int main(void){
	int Y,ans;
	int tmp=0;
	scanf("%d",&Y);	
	tmp=Y%4;
	if(tmp!=0){
		ans=0;
	}
	else{
		tmp=Y%100;
		if(tmp!=0){
			ans=1;
		}
		else{
			tmp=Y%400;
			if(tmp!=0){
			ans=0;
			}
			else ans=1;
		}
	}
	if(ans==0)	printf("Yes\n");
	if(ans==1)	printf("NO\n");

	return 0;
}