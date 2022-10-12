#include<stdio.h>

int main()
{
  char day[20];
  scanf("%s",day);
  
  //printf("%s",day);
  
  int ans=0;
  if (day[0] == 'M') ans = 5;
  else if(day[0] == 'T' && day[1] == 'u') ans = 4;
  else if(day[0] == 'W') ans = 3;
  else if(day[0] == 'T' && day[1] == 'h') ans = 2;
  else if(day[0] == 'F') ans = 1;
  
  printf("%d",ans);
  
  return 0;
}