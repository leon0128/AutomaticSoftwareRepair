#include<stdio.h>
int MIN(int a,int b){return a<b?a:b;}
int main(){
  int n,a,b,ans;
  scanf("%d %d %d",&a,&b,&n);
  ans=(n%3)*a;
  n-=n%3;
  ans+=MIN(n*a,n/3*b);
  printf("%d\n",ans);
  return 0;
}
