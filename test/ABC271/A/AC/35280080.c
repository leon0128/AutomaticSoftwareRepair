#include <stdio.h>
#include <math.h>

int main() {
  
  long int n;
  
  int a,b,c;
 
  scanf("%ld",&n);
 
  
  a=n/16;
  b=n%16;
  
  if(a==10)printf("A");
  if(a==11)printf("B");
  if(a==12)printf("C");
  if(a==13)printf("D");
  if(a==14)printf("E");
  if(a==15)printf("F");
  if(a<10)printf("%d",a);
  
  if(b==10)printf("A");
  if(b==11)printf("B");
  if(b==12)printf("C");
  if(b==13)printf("D");
  if(b==14)printf("E");
  if(b==15)printf("F");
  if(b<10)printf("%d",b);
  
  
 
  return 0;
}