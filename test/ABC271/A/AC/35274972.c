#include <stdio.h>

int main (void)
{
  int N;

  scanf("%d", &N);


  if (N <= 15)
  {
    printf("0%X", N);
  }
  else
  {
    printf("%X", N);
  }


  return 0;

}


