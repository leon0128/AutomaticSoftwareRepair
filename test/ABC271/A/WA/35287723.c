#include<stdio.h>
int main(){
	int N,ans,a,b,i;
  	char A[10];
  	char Henkan[16]="0123456789ABCDEF";
  	scanf("%d",&N);
  
  	while(N>0){
    	a=N%16;
      	N=N/16;
      	A[i]=Henkan[a];
      	i++;
    }
  	i--;
  	for(a=i;a>=0;a--){
    	printf("%02c",A[a]);
    }
	return 0;
}