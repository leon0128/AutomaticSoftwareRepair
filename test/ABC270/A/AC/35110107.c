#include <stdio.h>
#include <string.h>
int main(){
  int ret = 0;
  int a, b;
  scanf("%d%d", &a, &b);
  if( (a==1 || a==3 || a==5 || a==7 || b==1 || b==3 || b==5 || b==7) ){
    ret += 1;
  }
  if( (a==2 || a==3 || a==6 || a==7 || b==2 || b==3 || b==6 || b==7) ){
    ret += 2;
  }
  if( (a==4 || a==5 || a==6 || a==7 || b==4 || b==5 || b==6 || b==7) ){
    ret += 4;
  }
  printf("%d\n", ret);
  return 0;
}