#include<stdio.h>

int main(){
  int a, b, c, d, e, ans=1;
  
  scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
  
  if(a!=b)
  {
    ans++;
  }
  if(c!=a && c!=b)
  {
    ans++;
  }
  if(d!=a && d!=b && d!=c)
  {
    ans++;
  }
  if(e!=a && e!=b && e!=c && e!=d)
  {
    ans++;
  }
  
  printf("%d\n", ans);
  return 0;
}