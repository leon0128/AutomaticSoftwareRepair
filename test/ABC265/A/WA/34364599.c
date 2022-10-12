#include<stdio.h>
 
int main(void){
  int N,M;
  long long T;
  int A[100000];
  int X[100000];
  int Y[100000];
  int i;
  int p=1;
  int flag=1;
  scanf("%d %d %d",&N,&M,&T);
  
  for(int i=1;i<=N-1;i++){
  	scanf("%d",&A[i]);
  }
  for(i=1;i<=M;i++){
	scanf("%d %d",&X[i],&Y[i]);
  }
  for(i=1;i<=N-1;i++){
    if(T>A[i]){
      T=T-A[i];
      p=p+1;
 	}else{flag=0;break;}
    if(p=X[i]){T=T+Y[i];}
  }
  if(flag==1){printf("Yes");}
  if(flag==0){printf("No");}
  
  return 0;
}
