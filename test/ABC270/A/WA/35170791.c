#include<stdio.h>

int main(void)
{
  int A, B;
  scanf("%d %d", &A, &B);
  
  if(A == 0){
  	printf("%d", B);
  }else if(B == 0){
  	printf("%d", A);
  }else if(A == B){
  	printf("%d", A);
  }else if(A == 1 && B == 2){
  	printf("3");
  }else if(A == 1 && B == 3){
  	printf("3");
  }else if(A == 1 && B == 4){
  	printf("5");
  }else if(A == 1 && B == 5){
  	printf("5");
  }else if(A == 1 && B == 6){
  	printf("7");
  }else if(A == 2 && B == 1){
  	printf("3");
  }else if(A == 2 && B == 3){
  	printf("3");
  }else if(A == 2 && B == 4){
  	printf("6");
  }else if(A == 2 && B == 5){
  	printf("7");
  }else if(A == 2 && B == 6){
  	printf("6");
  }else if(A == 3 && B == 1){
  	printf("3");
  }else if(A == 3 && B == 2){
  	printf("3");
  }else if(A == 3 && B == 4){
  	printf("7");
  }else if(A == 3 && B == 5){
  	printf("7");
  }else if(A+B > 8){
  	printf("7");
  }else if(A == 4 && B == 1){
  	printf("5");
  }else if(A == 4 && B == 2){
  	printf("6");
  }else if(A == 4 && B == 3){
  	printf("7");
  }else if(A == 4 && B == 5){
  	printf("5");
  }
  
  
  return 0;
}