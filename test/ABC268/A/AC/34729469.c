#include<stdio.h>
int main(void){
  int wo[101];
  int cou;
  for(int i=0;i<101;i++) wo[i]=0;
  for(int i=0;i<5;i++){
    scanf("%d",&cou);
    wo[cou]=1;
  }
  cou=0;
  for(int i=0;i<101;i++) cou+=wo[i];
  printf("%d",cou);
  return 0;
}