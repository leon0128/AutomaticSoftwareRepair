#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

int main(void){
	int i,j,k,n;
	int count;
	int sum=0;
	int *a;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d",&j);
		sum+=j;
	}
	printf("%d",sum);
	return 0;
}