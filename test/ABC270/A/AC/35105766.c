#include <stdio.h>

int main ( void ){
	int a,b;
	scanf("%d %d",&a,&b);
	int i,j,k;
	int a1,a2,a3,b1,b2,b3;
	for(i = 0; i <= 1; i++){
		for(j = 0; j <= 1; j++){
			for(k = 0; k <= 1; k++){
				if( i + 2*j + 4*k == a ){
					a1 = i;
					a2 = j;
					a3 = k;
				}
				if( i + 2*j + 4*k == b ){
					b1 = i;
					b2 = j;
					b3 = k;
				}
			}
		}
	}
	int score = 0;
	if( a1 || b1 ) score += 1;
	if( a2 || b2 ) score += 2;
	if( a3 || b3 ) score += 4;
	printf("%d\n",score);
	return 0;
}