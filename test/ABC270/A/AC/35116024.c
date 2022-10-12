#include <stdio.h>

typedef enum {false, true} bool;

int main(void)
{
  int A, B, X;
  
  bool Z[3] = {false, false, false};
  
  scanf("%d %d", &A, &B);
  
  switch(A)
  {
    case 0:
         break;
    case 1:
         Z[0] = true;
         break;
    case 2:
         Z[1] = true;
         break;
    case 3:
         Z[0] = Z[1] = true;
         break;
    case 4:
         Z[2] = true;
         break;
    case 5:
         Z[0] = Z[2] = true;
         break;
    case 6:
         Z[1] = Z[2] = true;
         break;
    case 7:
         Z[0] = Z[1] = Z[2] = true;
  }
  
  switch(B)
  {
    case 0:
         break;
    case 1:
         Z[0] = true;
         break;
    case 2:
         Z[1] = true;
         break;
    case 3:
         Z[0] = Z[1] = true;
         break;
    case 4:
         Z[2] = true;
         break;
    case 5:
         Z[0] = Z[2] = true;
         break;
    case 6:
         Z[1] = Z[2] = true;
         break;
    case 7:
         Z[0] = Z[1] = Z[2] = true;
  }
  
  X = Z[0]*1+Z[1]*2+Z[2]*4;
  
  printf("%d\n", X);
  
  system("pause");
  
  return 0;
}