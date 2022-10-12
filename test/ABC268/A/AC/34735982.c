#include <stdio.h>

int main(void)
{
  int num[6], i, j, flag = 1;
  
  scanf("%d %d %d %d %d", &num[0], &num[1], &num[2], &num[3], &num[4]);
  
  i = 0;
  while (i < 5)
  {
    j = i + 1;
    while (j < 5)
    {
      if (num[i] == num[j])
        break;
      j++;
      if (j == 5)
        flag += 1;
    }
    i++;
  }
  
  printf("%d\n", flag);
  
  return (0);
}