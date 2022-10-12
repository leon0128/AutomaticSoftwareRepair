#include<stdio.h>
int main(){
  int N;
  scanf("%d",&N);
  
  int ans[2];
  int i,j;
  for(i=0;i<2;i++){
    ans[i]= N%16;
    if(N<16){
      if(i==0)ans[1]=0;
      break;
    }
    N /= 16;
  }
  
  for(i=1;i>=0;i--){
    if(ans[i] < 10) printf("%d", ans[i]);
    else{
      switch(ans[i]){
        case 10:
          printf("A");
          break;
        case 11:
          printf("B");
          break;
        case 12:
          printf("C");
          break;
        case 13:
          printf("D");
          break;
        case 14:
          printf("E");
          break;
        case 15:
          printf("F");
          break;
      }
    }
  }
  
  return 0;
}