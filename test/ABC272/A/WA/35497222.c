#include<stdio.h>

int main()
{
	int N; 
	scanf("%d",&N);
	int a,i, sum=0;
	for(i=0; i<N; i++){
		scanf("%d",&a);
		if(a>100||a<1)break;
		sum = sum + a;
	}
	(a>=1&&a<=100)?:printf("%d", sum),1;
	return 0;
 } 
