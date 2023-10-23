#include<stdio.h>

int main(){
	int a;
	scanf("%d",&a);
	if(a%4==0){
		if(a%400==0){
			puts("YES");
		}else if(a%100==0){
			puts("NO");
		}else puts("YES\n");
	}else puts("NO\n");
	return 0;
}