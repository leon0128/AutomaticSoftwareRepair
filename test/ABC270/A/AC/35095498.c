#include<stdio.h>
int main(void){
  int a,b,i,s=0,j=1;
  scanf("%d %d",&a,&b);
  for(i=0;i<3;i++){
    if(a%2==1 || b%2==1)
      s=s+j;
    a=a/2;
    b=b/2;
    j=j*2;
  }
  printf("%d",s);
  return 0;
}