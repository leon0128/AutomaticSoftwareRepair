#include <stdio.h>

int main(void)
{
  int a[5], num=5;;
  for(int i=0; i<5; i++)
  {
    scanf("%d", &a[i]);
  }
  
  for(int i=0; i<5; i++){
    for(int j=i+1; j<5; j++){
      if (a[i] == a[j]) {
        num--; break;
      }
    }
  }
  
  printf("%d", num);
  return 0;
}
