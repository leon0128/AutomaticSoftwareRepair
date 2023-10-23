#include <stdio.h>

int main(){
	int Y; // Yは、1000<=Y<=2999を満たす整数である。
	scanf("%d", &Y);
	if(Y%400==0){
		printf("YES\n"); //うるう年である。
	}else if(Y%100==0){
		printf("NO\n"); //うるう年ではない。
	}else if(Y%4==0){		
		printf("YES\n"); //うるう年である。	
	}else{
		printf("NO\n"); //うるう年ではない。
	}
	return 0;
}