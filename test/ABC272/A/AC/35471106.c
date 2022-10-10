#include<stdio.h>
int main(){
  int N;
  scanf("%d",&N);
  
  int i;
  int nArray[N];
  int ans=0;
  for(i=0;i<N;i++){
    scanf("%d",&nArray[i]);
    ans+=nArray[i];
  }
  
  printf("%d",ans);
  return 0;
}