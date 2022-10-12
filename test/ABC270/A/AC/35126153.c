#include <stdio.h>

int main(void)
{
  int a,b;
  int f[3] = {0,0,0};
  int ans = 0;
  
  scanf("%d %d",&a,&b);
  
  if (a == 1){
    f[2]++;
  } else if (a == 2){
    f[1]++;
  } else if (a == 3){
    f[1]++;
    f[2]++;
  } else if (a == 4){
    f[0]++;
  } else if (a == 5){
    f[0]++;
    f[2]++;
  } else if (a == 6){
    f[0]++;
    f[1]++;
  } else if (a == 7){
    f[0]++;
    f[1]++;
    f[2]++;
  }
  
  if (b == 1){
    f[2]++;
  } else if (b == 2){
    f[1]++;
  } else if (b == 3){
    f[1]++;
    f[2]++;
  } else if (b == 4){
    f[0]++;
  } else if (b == 5){
    f[0]++;
    f[2]++;
  } else if (b == 6){
    f[0]++;
    f[1]++;
  } else if (b == 7){
    f[0]++;
    f[1]++;
    f[2]++;
  }
  
  if (f[0] > 0) ans += 4;
  if (f[1] > 0) ans += 2;
  if (f[2] > 0) ans += 1;
  
  printf("%d\n",ans);
  return 0;
}