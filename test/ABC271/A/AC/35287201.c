#include<stdio.h>
#include<stdlib.h>

int main(){
  int N,a,b;
  char string[] = "Stringasdfgkdf";
  scanf("%d",&N);
  a = N%16;
  b = N/16;
  
  if(b<10)printf("%d",b);
  else if(b==10)printf("A");
  else if(b==11)printf("B");
  else if(b==12)printf("C");
  else if(b==13)printf("D");
  else if(b==14)printf("E");
  else printf("F");
  if(a<10)printf("%d",a);
  else if(a==10)printf("A");
  else if(a==11)printf("B");
  else if(a==12)printf("C");
  else if(a==13)printf("D");
  else if(a==14)printf("E");
  else if(a==15)printf("F");
}