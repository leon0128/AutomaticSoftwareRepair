#include<stdio.h>

int main(){
int a, b ,c;
int d=0;
  scanf("%d %d %d",&a,&b,&c);
  //printf("%d %d %d",a,b,c);
  if(a*3<b){
    printf("%d",a*c);
  }else{
    d=c%3;
    c=c/3;
    printf("%d",a*d+b*c);
  }
    

  return(0);
}