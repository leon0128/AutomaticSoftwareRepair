#include <stdio.h>

int main(void)
{
  char x, y;
  scanf("%c",&x);
  scanf("%c",&y);
  if(x=='M'){
    printf("5");
  }else if(x=='W'){
    printf("3");
  }else if(x=='F'){
    printf("1");
  }else if(x=='T'){
    if(y=='u'){
      printf("4");
    }else{
      printf("2");
    }
  }
  printf("\n");
  return 0;
}