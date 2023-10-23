#include <stdio.h>
#include <stdlib.h>

int main(){
	int x;

	scanf("%d",&x);

	if(x%400!=0){
		if(x%100!=0){
			if(x%4!=0){
				printf("NO\n");
			}
			else{
				printf("YES\n");
			}
		}
		else{
			printf("NO\n");
		}
	}
	else{
		printf("YES\n");
	}

	return 0;

}