#include<stdio.h>

int main(void){
  unsigned int year;
  scanf("%u",&year);
  if(year%4==0 && year%100 || year%400==0) puts("YES");
  else puts("NO");
  return 0;
}
