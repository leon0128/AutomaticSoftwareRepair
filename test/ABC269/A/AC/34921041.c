#define _DEBUG 0

#include <stdio.h>
#include <stdbool.h>//bool型
#include <string.h>// memset(abUse, false, sizeof(abUse));//文字数 = strlen();//0 == strcmp(,);//一致//strcpy(buff, "abcdefg");
//#include <stdlib.h>//絶対値=abs(),絶対値long型=labs(),kazu=atoi(moji),malloc,free
//#include <math.h>//平方根=sqrt();double pow(double x, double y);
//#include <unistd.h>//fflush(stdout);
typedef unsigned long Ulong;
typedef unsigned int Uint;
typedef unsigned short Ushort;
typedef unsigned char Uchar;
typedef unsigned long long Ulonglong;
typedef signed long long longlong;
//u, d, lu, ld, llu, lld
int main (void)
{
  int a, b, c,d;
  scanf("%d %d %d %d", &a, &b, &c, &d);
  
  int ans = (a+b)*(c-d);
  printf("%d\nTakahashi", ans);
  
  return 0;
}