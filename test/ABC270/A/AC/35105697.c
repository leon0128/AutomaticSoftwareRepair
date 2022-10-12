#include<stdio.h>
int main(void)
{
  int A,B,C = 0,D,E,i = 4;
  scanf("%d %d",&A,&B);

  D = A;
  E = B;

while(i > 0)
  {
    if(D / i == 1 || E / i == 1)
    {
      C = C + i;
      if(D / i == 1)
        D = D - i;
      if(E / i == 1)
        E = E - i;
    }
      i = i / 2;
  }

printf("%d",C);

  return 0;
}
