#include<stdio.h>
int main(){
  char a[100];
  int i;
  for(i=0;scanf("%c",&a[i]) && a[i]>='a' && a[i]<='z';i++)
  {
      
  }
  i--;
  char ans=a[i/2];
  printf("%c",ans);
  
  return 0;
}