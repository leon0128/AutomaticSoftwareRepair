#include <stdio.h>

int main( void)
{
  int year, flag = 0;
  
  scanf( "%d", &year);
 
  if ( year % 400 == 0) flag = 1;
  else if ( year % 100 == 0) flag = 0;
  else if ( year % 4 == 0) flag = 1;
  else flag = 0;

  if ( flag == 1) puts( "YES");
  else puts( "NO");
  
  return 0;
}
