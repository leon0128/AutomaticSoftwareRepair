#include <stdio.h>

main(){
	int a,b,c,x = 0;
	scanf("%d %d %d",&a,&b,&c);
	if(a * 3 > b){
		x = (c / 3 * b )+ (c % 3 *a);
		printf("%d",x);
	}
	else{
		printf("%d",a*c);
	}
	
}