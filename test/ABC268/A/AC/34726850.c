#include<stdio.h>
int main(){
  int b[110]={},i,s=0,a;
  for(i=0;i<5;i++){
    scanf("%d",&a);
    s+=1-b[a];
    b[a]=1;
  }
  printf("%d\n",s);
  return 0;
}
