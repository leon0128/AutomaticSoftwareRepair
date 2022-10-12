#define _DEBUG 0

#include <stdio.h>
#include <stdbool.h>//bool型
#include <string.h>//0 == strcmp(,);//一致// memset(abUse, false, sizeof(abUse));//strcpy(buff, "abcdefg");
//#include <stdlib.h>//絶対値=abs(),絶対値long型=labs(),kazu=atoi(moji),malloc,free
//#include <math.h>//平方根=sqrt();double pow(double x, double y);
//#include <unistd.h>//fflush(stdout);
typedef unsigned long Ulong;
typedef unsigned int Uint;
typedef unsigned short Ushort;
typedef unsigned char Uchar;
typedef unsigned long long Ulonglong;
typedef signed long long longlong;

int main (void)
{
  int x;
  int y;
  int n;
  
  long i, j, k;
  
  scanf("%d", &x);
  scanf("%d", &y);
  scanf("%d", &n);
  
  if (x*3 < y)
  {
    printf("%d", n*x);
  }
  else
  {
    int a = n / 3;
    int b = n % 3;
    
    printf("%d", a*y + b*x);
  }
  
  return 0;
}