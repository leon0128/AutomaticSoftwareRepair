#include<stdio.h>

int main()
{
	int N; 
	scanf("%d",&N);
	int a,i, sum=0;
	for(i=0; i<N; i++){
		scanf("%d",&a);
		sum = sum + a;
	}
	printf("%d", sum),1;
	return 0;
 } 
