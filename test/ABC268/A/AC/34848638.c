#include<stdio.h>
#include<string.h>
int main (void){
	
	int arr[10]={0};
	
	int n,flag=0;
	int i=0,x=0;
	for(i=0;i<5;i++){
		
		scanf("%d",&n);
		int j,f=0;
		if(flag==0 && n==0){
			flag=1;
			x++;
		}
		for(j=0;j<10;j++){
			if(arr[j]==n){
				f=1;
				break;
			}
		}
		if(f==0){
			arr[x]=n;
			x++;
		}
		
	}
	
	printf("%d",x);
	
}