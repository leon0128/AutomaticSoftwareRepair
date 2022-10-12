#include<stdio.h>

int main(){
  int a,b,x,y,n,total,min=20000;
  /*a:X円払ってりんごを1つ貰う回数*/
  /*b:Y円払ってりんごを3つ貰う回数*/
  scanf("%d%d%d",&x,&y,&n);
  for(b=0;b<=n/3;b++){
    a=n-3*b;
    if(a>=0)total=a*x+b*y;
    if(min>total)min=total;
  }
  printf("%d",min);
  
  return 0;
}