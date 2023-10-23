#include <stdio.h>
#include <string.h>
#include <math.h>
#include <memory.h>
#include <stdlib.h>


int main(void)
{	
	int y;
	scanf("%d",&y);
	
	if(y%400==0){
		printf("YES\n");
	} else if(y%100==0){
		printf("NO\n");
	} else if(y%4==0){
		printf("YES\n");
	} else{
		printf("NO\n");
	}
	return 0;
}
