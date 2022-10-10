#include<stdio.h>
int main(){
	int n,sum=0;
    scanf("%d\n",&n);
  	int arr[n];
  	
  	for(int i=0;i<=n-1;i++){
      scanf("%d",&arr[i]);
      sum=sum+arr[i];
    }
  printf("%d\n",sum);
 
  	return 0;
}