#include <stdio.h>

int main (void)
{
  int num[5] = {0};
  int check[5] = {0};
  int total = 0;
  int i, j;

  for (i = 0; i < 5; i++)
  {
    scanf("%d", &num[i]);
  }

  check[total] = num[0];
  total++;

  for (i = 1; i < 5; i++)
  {
    int flag = 0;

    for (j = 0; j < i; j++)
    {
      if(check[j] == num[i])
      {
        flag = 1;
        break;
      }
    }
    
    if (flag == 0)
    {
      check[total] = num[i];
      total++;
    }
  }

  printf("%d", total);

  return 0;

}


