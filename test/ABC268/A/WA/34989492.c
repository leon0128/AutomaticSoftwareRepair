#include<stdio.h>
int main(void){
  int x[5],i,j,cnt=0;
  for(i=0;i<5;i++){
    scanf("%d",&x[i]);
  }
  for(i=0;i<5;i++){
    for(j=i+1;j<5;j++){
      //printf("%d,%d\n",x[i],x[j]);
      if(x[i]==x[j]){
        cnt++;
      }
    }
  }
  printf("%d\n",cnt);
  return 0;
}