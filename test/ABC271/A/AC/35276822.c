#define _DEBUG 0

#include <stdio.h>
#include <stdbool.h>//bool型
#include <string.h>// memset(abUse, false, sizeof(abUse));//文字数 = strlen();//0 == strcmp(,);//一致//strcpy(buff, "abcdefg");if (strstr(t, s))//部分一致
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
  int n;
  scanf("%d", &n);
  char s[10];//文字列入力用
  s[0] = n/16;
  if (10 <= s[0])
  {
    s[0]+=55;
  }
  else
  {
    s[0]+=48;
  }
  s[1] = n%16;
  if (10 <= s[1])
  {
    s[1]+=55;
  }
  else
  {
    s[1]+=48;
  }
  s[2] = 0;
  printf("%c%c", s[0], s[1]);
  
  return 0;
}