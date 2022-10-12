#include<stdio.h>

int main(void)
{
  int A,B,C,X;
  
  scanf("%d %d",&A,&B);
  
  X=A+B;
 
  if(A==0){
    C=B;
  }else if(A==1){
    if(B==1){
      C=1;
    }else if(B==2){
      C=3;
    }else if(B==3){
      C=3;
    }else if(B==4){
      C=5;
    }else if(B==5){
      C=5;
    }else if(B==6){
      C=7;
    }else{
      C=7;
    }
  }else if(A==2){
    if(B==1){
      C=3;
    }else if(B==2){
      C=2;
    }else if(B==3){
      C=3;
    }else if(B==4){
      C=6;
    }else if(B==5){
      C=7;
    }else if(B==6){
      C=6;
    }else{
      C=7;
    }
  }else if(A==3){
    if(B==1){
      C=3;
    }else if(B==2){
      C=3;
    }else if(B==3){
      C=3;
    }else if(B==4){
      C=7;
    }else if(B==5){
      C=7;
    }else if(B==6){
      C=7;
    }else{
      C=7;
    }
  }else if(A==4){
    if(B==1){
      C=5;
    }else if(B==2){
      C=6;
    }else if(B==3){
      C=7;
    }else if(B==4){
      C=4;
    }else if(B==5){
      C=5;
    }else if(B==6){
      C=6;
    }else{
      C=7;
    }
  }else if(A==5){
    if(B==1){
      C=5;
    }else if(B==2){
      C=7;
    }else if(B==3){
      C=5;
    }else if(B==4){
      C=5;
    }else if(B==5){
      C=5;
    }else if(B==6){
      C=7;
    }else{
      C=7;
    }
  }else if(A==6){
    if(B==1){
      C=7;
    }else if(B==2){
      C=6;
    }else if(B==3){
      C=7;
    }else if(B==4){
      C=6;
    }else if(B==5){
      C=7;
    }else if(B==6){
      C=6;
    }else{
      C=7;
    }
  }else{
    C=7;
  }
  
  printf("%d",C);
  
  return 0;
}