#include<stdio.h>
#include<string.h>
int main(){
  char input_string[200] ;
  int a , b , c , d , e ;
  int aaa;
  int numberidx ;
  int number[10];
  int alreadynumber[10];
  int answer = 5;
  
  for(int idx; idx < 10 ; idx++){
    number[idx] = 0;
    alreadynumber[idx] = -1;
  }
  
  scanf("%d %d %d %d %d" , &number[0], &number[1] , &number[2] , &number[3] ,&number[4] ) ;
  
  for(int idx = 0 ; idx < 5 ; idx++){
    if(number[idx] == -1){
      continue;
    }
    for(int idx2 = idx + 1 ; idx2 < 5 ; idx2++){
      if(number[idx]  == number[idx2] ){
        answer--;
        number[idx2] = -1;
      }
    }
    
  }

  printf("%d\n" , answer);
  
  return 0;
  
}