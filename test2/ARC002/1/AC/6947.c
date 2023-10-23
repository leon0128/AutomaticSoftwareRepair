#include<stdio.h>
int main(){
	int n;
	scanf("%d",&n);
	if(n%4==0){
		if(n%100==0){
			if(n%400==0){
				printf("YES\n");
			}else printf("NO\n");
		}else printf("YES\n");
	}else printf("NO\n");
	return 0;
}
