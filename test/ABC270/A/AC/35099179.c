#include <stdio.h>
#include <math.h>

int main() {
  
  int a,b,c;
  
  int x=0;
  int y=0;
  int z=0;
  
  
  scanf("%d %d",&a,&b);
  
 
  if(a/4>0){z=1;}
  if(b/4>0){z=1;}
  a=a%4;
  b=b%4;
  if(a/2>0){y=1;}
  if(b/2>0){y=1;}
  a=a%2;
  b=b%2;
  if(a>0){x=1;}
  if(b>0){x=1;}
  
  c=1*x+2*y+4*z;
  
  printf("%d",c);
  
  
  return 0;
}