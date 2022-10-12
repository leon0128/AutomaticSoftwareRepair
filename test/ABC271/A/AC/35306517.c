#include<stdio.h>
int main(){
	int N,ans,a,b,i;
  	char A[10];
  	char Henkan[16]="0123456789ABCDEF";
  	scanf("%d",&N);
  	b=N;
	i=0;
  	while(N>0){
    	a=N%16;
      	N=N/16;
      	A[i]=Henkan[a];
      	i++;
    }
  	i--;
    if(b==0) printf("00");
  	else{
  		for(a=i;a>=0;a--){
          if(b<16){
          	printf("0");
          }
           printf("%c",A[a]);
    	}
    }

	return 0;
}