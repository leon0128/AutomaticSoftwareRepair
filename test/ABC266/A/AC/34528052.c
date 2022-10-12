#include<stdio.h>
int main(){
  char a[100];
  scanf("%s",a);
  int sz = strlen(a);
  char ans=a[sz/2];
  printf("%c",ans);
  
  return 0;
}