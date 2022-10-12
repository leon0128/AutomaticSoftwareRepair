#include <stdio.h>
int main(void){
  int a,b,is_get1[3],is_get2[3],ans[3];
  scanf("%d %d",&a,&b);
  
  for(int i=0;i<8;i++){
    int tmp=0;
    for(int j=0;j<3;j++){
      is_get1[j]=0;
      if(i&(1<<j)){
        is_get1[j]=1;
        tmp+=(1<<j);
      }
    }
    if(tmp==a){
      break;
    }
  }
  for(int i=0;i<8;i++){
    int tmp=0;
    for(int j=0;j<3;j++){
      is_get2[j]=0;
      if(i&(1<<j)){
        is_get2[j]=1;
        tmp+=(1<<j);
      }
    }
    if(tmp==b){
      break;
    }
  }
  int answer=0;
  int x=1;
  for(int i=0;i<3;i++){
    ans[i]=(is_get1[i]|is_get2[i]);
    answer+=x*ans[i];
    x*=2;
  }
  printf("%d\n",answer);
  return 0;
}