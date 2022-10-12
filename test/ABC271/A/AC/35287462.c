#include<stdio.h>

void print_sixteen(int k)
{
  if(k<10){
    printf("%d",k);
  }
  else{
    switch(k%10){
      case 0:
        printf("A");
        break;
      case 1:
        printf("B");
        break;
      case 2:
        printf("C");
        break;
      case 3:
        printf("D");
        break;
      case 4:
        printf("E");
        break;
      case 5:
        printf("F");
        break;
      default:
        break;
    }
  }
}

int main(void)
{
  int n;
  scanf("%d",&n);
  print_sixteen(n/16);
  print_sixteen(n%16);
  return 0;
}
  