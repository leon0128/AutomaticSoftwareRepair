#include <stdio.h>

int main(void) {
	int y, n=0;
	
	scanf("%d", &y);
	
	if(y%4==0){
		if(y%100==0){
			if(y%400==0)
			n++;
		}
		else
		n++;
	}
	
	if(n==1)
	printf("YES\n");
	else
	printf("NO\n");
	return 0;
}
