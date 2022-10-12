#include <stdio.h>
 
int main()
{
  int a;
  int x[5];
  a = scanf("%d", &x[0]);
  a = scanf("%d", &x[1]);
  a = scanf("%d", &x[2]);
  a = scanf("%d", &x[3]);
  a = scanf("%d", &x[4]);
  
  int cnt = 0;
  int L = 5;
  for(int i=0; 4> i; i++)
  {
    for(int k=i+1; L>k; k++){
      if(x[i] == x[k]) cnt++;
    }
    L--;
  }
  printf("%d\n",cnt+1);
  return 0;
}