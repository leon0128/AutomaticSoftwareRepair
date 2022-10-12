#include <stdio.h>
 
int main (void){
	int rest_B, rest_A, check_num, A, B, C = 0;
  	int C_scor[5] = {0};
  	scanf("%d %d", &A, &B);
  
  	if(A < 3) {
      C_scor[A] = 1; 
    }
  	
  	else if(A == 3){
      C_scor[2] = 1;
      C_scor[1] = 1;
    }
  	
  	else if(A >= 4){
      C_scor[4] = 1;
      if(A > 4){
        rest_A = A - 4;
        if(rest_A == 3){
          C_scor[2] = 1;
          C_scor[1] = 1;
        }
        
        else if(rest_A == 2){
          C_scor[2] = 1;
        }
        
        else if(rest_A == 1){
          C_scor[1] = 1;
        }
        
      }
    }
  
  	if(B < 3) {
      C_scor[B] = 1; 
    }
  	
  	else if(B == 3){
      C_scor[2] = 1;
      C_scor[1] = 1;
    }
  	
  	else if(B >= 4){
      C_scor[4] = 1;
      if(B > 4){
        rest_B = B - 4;
        if(rest_B == 3){
          C_scor[2] = 1;
          C_scor[1] = 1;
        }
        
        else if(rest_B == 2){
          C_scor[2] = 1;
        }
        
        else if(rest_B == 1){
          C_scor[1] = 1;
        }
        
      }
    }
  	
  	for(check_num = 1; check_num < 5; check_num++){
      C += C_scor[check_num] ? check_num : 0;
    }
  	
  	printf("%d", C);
}