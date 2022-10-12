#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(void)
{
  int a, b;
  scanf("%d %d",&a,&b);
  
  int c = 0, d[3];
  d[0] = 0; d[1] = 0; d[2] = 0;
  if(a>=4){
    d[2] = 1;
    a = a-4;
  }
  if(b>=4){
    d[2] = 1;
    b = b-4;
  }
  if(a>=2){
    d[1] = 1;
    a = a-2;
  }
  if(b>=2){
    d[1] = 1;
    b = b-2;
  }
  if(a==1){
    d[0] = 1;
  }
  if(b==1){
    d[0] = 1;
  }
  
  if(d[0] == 1) c = c+1;
  if(d[1] == 1) c = c+2;
  if(d[2] == 1) c = c+4;
  
  printf("%d\n",c);
  return 0;
}