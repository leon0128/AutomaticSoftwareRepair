#include <stdio.h>

void check_score(int x, int *f);

int main (void)
{
  int A, B;
  int flag_Takahashi[3] = {0};
  int flag_Aoki[3] = {0};
  int score = 0;

  scanf("%d %d", &A, &B);

  check_score(A, flag_Takahashi);
  check_score(B, flag_Aoki);

  if (flag_Takahashi[0] == 1 || flag_Aoki[0] == 1)
  {
    score += 1;
  }

  if (flag_Takahashi[1] == 1 || flag_Aoki[1] == 1)
  {
    score += 2;
  }

  if (flag_Takahashi[2] == 1 || flag_Aoki[2] == 1)
  {
    score += 4;
  }

  printf("%d", score);


  return 0;

}


void check_score(int x, int *f)
{
  if(x == 7)
  {
    f[0] = 1;
    f[1] = 1;
    f[2] = 1;
  }
  else if (x == 6)
  {
    f[1] = 1;
    f[2] = 1;
  }
  else if (x == 5)
  {
    f[0] = 1;
    f[2] = 1;
  }
  else if (x == 4)
  {
    f[2] = 1;
  }
  else if (x == 3)
  {
    f[0] = 1;
    f[1] = 1;
  }
  else if (x == 2)
  {
    f[1] = 1;
  }
  else if (x == 1)
  {
    f[0] = 1;
  }
}