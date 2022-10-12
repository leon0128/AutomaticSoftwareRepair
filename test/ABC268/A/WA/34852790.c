#include <stdio.h>

int main(void)
{
  int a[5], i, j, z=0, seisu=1;
  
  scanf("%d%d%d%d%d", &a[0], &a[1], &a[2], &a[3], &a[4]);
  
  for(i=1; i<5; i++)
  {
    for(j=0; j<i; j++)
    {
      if(a[i]==a[j])
        z++;
    }
  
    if(z==0)
      seisu++;
  }
  
  printf("%d", seisu);
  
  return 0;
}