#include <stdio.h>

int main(void)
{
  int n;
  
  scanf("%d",&n);
  if (n/16 == 10) printf("A");
  else if (n/16 == 11) printf("B");
  else if (n/16 == 12) printf("C");
  else if (n/16 == 13) printf("D");
  else if (n/16 == 14) printf("E");
  else if (n/16 == 15) printf("F");
  else printf("%d",n/16);
  
  if (n%16 == 10) printf("A");
  else if (n%16 == 11) printf("B");
  else if (n%16 == 12) printf("C");
  else if (n%16 == 13) printf("D");
  else if (n%16 == 14) printf("E");
  else if (n%16 == 15) printf("F");
  else printf("%d\n",n%16);
  return 0;
}