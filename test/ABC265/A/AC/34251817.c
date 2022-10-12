#include<stdio.h>
int main(void){
  int x,y,n,a,t;
  scanf("%d %d %d",&x,&y,&n);
  if(x*3<y){
    printf("%d",x*n);
  }
  else{
    a=n/3;
    t=n-3*a;
    printf("%d",t*x+a*y);
  }
  return 0;
}