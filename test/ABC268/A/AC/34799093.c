#include<stdio.h>
int main(void)
{
  int A,B,C,D,E,count=1;
  
  scanf("%d" "%d" "%d" "%d" "%d",&A,&B,&C,&D,&E);
  
  if(B != A){
    count++;
  }
  if(C != A && C != B){
    count++;
  }
  if(D != A && D != B && D != C){
    count++;
  }
  if(E != A && E != B && E != C && E != D){
    count++;
  }
  
  printf("%d\n",count);
  return 0;
}