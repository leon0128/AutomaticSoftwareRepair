#include<stdio.h>
int main(void){
  int N;
  scanf("%d",&N);
  int ans=0;
  for(int i=0;i<N;i++){
    int A;
    scanf("%d",&A);
    ans+=A;
  }
  printf("%d",ans);
  return 0;
}