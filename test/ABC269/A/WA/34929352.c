#include<stdio.h>
#include<stdlib.h>
int main(){
  int a,b,c,d;
  if(scanf("%d%d%d%d",&a,&b,&c,&d)){
      int result=(a+b)*(c-d);
     printf("%d",result);
     printf("Takahashi");
  }
  return 0;
}