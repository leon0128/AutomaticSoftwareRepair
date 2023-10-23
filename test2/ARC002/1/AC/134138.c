#include <stdio.h>

/* AtCoder Regular Contest #002 A - うるう年 */
int main(){
	int input;
	scanf( "%d", &input );
	
	if( input%400 == 0 ){
		printf("YES\n");
	}else if( input%100 != 0 && input%4 == 0){
		printf("YES\n");
	}else{
		printf("NO\n");
	}
	return 0;
}