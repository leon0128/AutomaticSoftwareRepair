#include<stdio.h>

int main(){
  int N[100], i=0, sum=0;
  
  do{
  (void)scanf("%d",&i);
    getchar();
  }while(i < 1 && 100 < i);
  
  while(i != 1){
    
    do{
      (void)scanf("%d",&N[i]);
      getchar();
    }while(N[i] < 1 && 100 < N[i]);
    
    sum+=N[i];
    i--;
  }
  
  printf("%d",sum);
}