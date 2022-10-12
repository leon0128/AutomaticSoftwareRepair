#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

int main(void){
	int i,j,k,n;
	int count=0;
	bool d;
	int x[5]={-1,-1,-1,-1,-1};
	for(i=0;i<5;i++){
		d=false;
		scanf("%d",&k);
		for(j=0;j<i;j++){
			if(x[j]==k){
				d=true;
			}
		}
		if(!d){
			x[i]=k;
			count++;
		}
	}
	printf("%d",count);
	return 0;
}