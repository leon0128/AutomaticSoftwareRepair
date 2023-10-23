#include<stdio.h>
int judge(int year){
	int flag;
	if(!(year%400)){
		flag=1;
	}
	else if(!(year%100)){
		flag=0;
	}
	else if(!(year%4)){
		flag=1;
	}
	else{
		flag=0;
	}
	return flag;
}
int main(){
	int year;
	int flag;
	
	scanf("%d",&year);
	flag=judge(year);
	
	if(flag){
		printf("YES\n");
	}
	else{
		printf("NO\n");
	}
	return 0;
}