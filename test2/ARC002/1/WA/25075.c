#include<stdio.h>

int main(){
	
	int year,j=0;
	scanf("%d",&year);
	
	
	
	if((year%4==0 || year%400==0) && year%100!=0){
		
		j=1;
		
		
	}else{
		
	}
	
		if(j==1){
			printf("YES\n");
		}else{
			printf("NO\n");
		}
		
		return 0;
		
	}

