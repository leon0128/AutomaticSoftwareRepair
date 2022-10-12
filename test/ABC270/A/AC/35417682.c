#include<stdio.h>
#include<math.h>

int main(){
  
  int a,b,A=0,B=0,C=0;   /*A,B,Cは各１点、２点、４点の問題の正解の有無を１、０で表す*/
  scanf("%d%d",&a,&b);
  
  if(a-4>=0){
    C++;
    a = a-4;
  }
  if(a-2>=0){
    B++;
    a = a-2;
  }
  if(a==1) A++;
  
  if(b-4>=0 && C==0){
    C++;
    b = b-4;
  }
  if(b-2>=0 && B==0){
    B++;
    b = b-2;
  }
  if(b==1 && A==0) A++;
  
  int S=0;
  if(A!=0) S=S+1;
  if(B!=0) S=S+2;
  if(C!=0) S=S+4;
  
  printf("%d",S);
  
  return 0;
}
