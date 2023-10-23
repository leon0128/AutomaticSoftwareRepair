#include <stdio.h>

int uru(int y){
	if (y%400==0)return 1;
	if (y%100==0)return 0;
	if (y%4==0)return 1;
	
	return 0;
}

int main(){
	int y,a[3],t;
	
	scanf("%d",&y);
	
	t=uru(y);
	if(t==0)printf("NO\n");
	if(t==1)printf("YES\n");
	
	return 0;
}