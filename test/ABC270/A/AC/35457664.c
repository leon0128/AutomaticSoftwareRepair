#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
  int A ,B,ans=0;
  scanf("%d %d",&A,&B);
  int x[3];
  for(int i=0;i<3;i++){
    x[i]=0;
    if(A%2==1 || B%2==1){
      x[i]=1;
    }
    A=A/2;
    B=B/2;
  }
  for(int i=0;i<3;i++){
    if(x[i]==1)ans += pow(2,i);      
  }
  printf("%d",ans);
}
  