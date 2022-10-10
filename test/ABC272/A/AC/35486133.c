#include<stdio.h>

int main(){
  int N[100], i=0, sum=0;
  
  do{
  scanf("%d",&i);  
  }while(i < 1 && 100 < i);
  
  while(i != 0){
    
    do{
      scanf("%d",&N[i]);
    }while(N[i] < 1 && 100 < N[i]);
    
    sum+=N[i];
    i--;
  }
  
  printf("%d",sum);
}