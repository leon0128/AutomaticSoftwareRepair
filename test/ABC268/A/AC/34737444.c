#include<stdio.h>
int main(){
  int input[5] = {0,0,0,0,0};
  int count[5] = {0,0,0,0,0};
  int i,j;
  int ans = 1;
  for (i=0;i<5;i++){
    scanf("%d",&input[i]);
  }
  
  for (i=0;i<4;i++){
    int flag = 0;
    for(j=i+1;j<5;j++){
      if(input[i]==input[j]){
        flag = 1;
      }
    }
    if(flag==0) ans++;
  }
  
  printf("%d",ans);
  return 0;
}