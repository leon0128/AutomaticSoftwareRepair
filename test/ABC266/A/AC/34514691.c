#include<stdio.h>
int main(void)
{
  int a,b,count=0;
  char z[100];
  
  scanf("%s",z);
  
  for(a=0;z[a] != '\0';a++){
    count++;
  }
  
  b = count / 2;
  
  printf("%c\n",z[b]);
  return 0;
}