#include <stdio.h>

int main (void)
{
  int N;
  int A[100];
  int sum = 0;
  int i;

  scanf("%d", &N);

  for (i = 0; i < N; i++)
  {
    scanf("%d", &A[i]);
    sum += A[i];
  }

  printf("%d", sum);

  return 0;

}


