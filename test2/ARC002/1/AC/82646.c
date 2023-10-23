#include <stdio.h>

int main(){
	int year;
	scanf("%d",&year);
	if(0 == year % 4){
		if(0 == year %100){
			if(0 == year % 400)
				printf("YES");
			else
				printf("NO");
		}
		else{
			printf("YES");
		}
			
	}else{
		printf("NO");
	}
	printf("\n");
	return 0;
}