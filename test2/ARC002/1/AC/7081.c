#include <stdio.h>
#include <stdlib.h>

int main(){
	int y, result;

	scanf("%d", &y);

	if(y%4==0){
		if(y%100==0){
			if(y%400==0){
				result = 1;
			}else{
				result = 0;
			}
		}else{
			result = 1;
		}
	}else{
		result = 0;
	}

	if(result==1){
		printf("YES\n");
	}else{
		printf("NO\n");
	}

	return 0;
}
