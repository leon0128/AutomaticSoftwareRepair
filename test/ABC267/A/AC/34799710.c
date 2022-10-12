#include<stdio.h>
int main(void)
{
  int a,b;
  char c[10];
  
  scanf("%s",c);
  
  if(c[0] == 'M'){
    printf("5\n");
  }
  else if(c[0] == 'W'){
    printf("3\n");
  }
  else if(c[0] == 'F'){
    printf("1\n");
  }
  else if(c[0] == 'T'){
    if(c[1] == 'u'){
      printf("4\n");
    }
    else{
      printf("2\n");
    }
  }
  return 0;
}