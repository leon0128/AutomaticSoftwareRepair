#include <stdio.h>

int main(void){
  int a[5];
  for(int i=0;i<5;i++){
    scanf("%d",&a[i]);
  }

  int is_same[5]={0,0,0,0,0};
  int cnt=5;
  
  for(int i=0;i<4;i++){
    for(int j=i+1;j<5;j++){
      if(a[i]==a[j]&& is_same[j]==0){
        is_same[j]=1;
        cnt--;
      }
    }
  }
  printf("%d\n",cnt);
  return 0;

}