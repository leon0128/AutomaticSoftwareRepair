#include<stdio.h>
#include<stdlib.h>

int main(){
  int n,a[100],i,sum=0;
  scanf("%d",&n);
  for (i=0; i<n; i++){
  	scanf("%d",a+i);
  }
   for (i=0; i<n; i++){
  	sum+=*(a+i);
  }
  printf("%d", sum);
  
	return 0;
}