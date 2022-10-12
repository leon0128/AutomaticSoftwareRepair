#include<stdio.h>
 
void test_1_2_4(int A, int B){
 int rest_scor, C = 0, check_num;
 int C_scor[5] = {0};
   if(A > 4){
     rest_scor = A - 4;
     C_scor[4] = 1;
     if(rest_scor == 3){
       C_scor[2] = 1;
       C_scor[1] = 1;
     }
     if(rest_scor == 2){
       C_scor[2] = 1;
     }
     if(rest_scor == 1){
       C_scor[1] = 1;
     }
   }
  if(B > 4){
     rest_scor = B - 4;
     C_scor[4] = 1;
     if(rest_scor == 3){
       C_scor[2] = 1;
       C_scor[1] = 1;
     }
     if(rest_scor == 2){
       C_scor[2] = 1;
     }
     if(rest_scor == 1){
       C_scor[1] = 1;
     }
   }
  if(A == 3 || B == 3){
       C_scor[2] = 1;
       C_scor[1] = 1;
   }
	
  if(A < 3){ 
     C_scor[A] = 1;
  }
  if(B < 3){
    C_scor[B] = 1;
  }
  
  for(check_num = 1; check_num < 5; check_num++){
    C += C_scor[check_num] ? 1 : 0;
  }
      printf("%d", C);
}
 
int main (){
  int A, B;
  
  scanf("%d %d", &A, &B);
  test_1_2_4(A, B);
  return 0; 
}