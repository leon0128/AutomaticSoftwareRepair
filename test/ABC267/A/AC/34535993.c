#include <stdio.h>
int main()
{
  char s[10];
  scanf("%s", s);
  int ans;
  if(s[0] == 'M')
    ans = 5;
  else if(s[0] == 'T'){
    if(s[1] == 'u')
      ans = 4;
    else
      ans = 2;
  }else if(s[0] == 'W')
    ans = 3;
  else
    ans = 1;
  printf("%d\n", ans);
  return 0;
}