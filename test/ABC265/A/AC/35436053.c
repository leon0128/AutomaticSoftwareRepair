#include<stdio.h>
int main(){
  int x,y,n;
  scanf("%d %d %d",&x,&y,&n);
  int apple3=3*x;
  if(y<3*x){
    apple3=y;
  }
  int ans=n/3*apple3+(n%3)*x;
  printf("%d\n",ans);
  return 0;
}