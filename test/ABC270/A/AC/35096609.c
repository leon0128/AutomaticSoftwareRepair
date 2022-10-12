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
  int a;
  int b;
  scanf("%d", &a);
  scanf("%d", &b);

  int c1[3];
  int c2[3];
  c1[0] = a&1;
  c1[1] = a&2;
  c1[2] = a&4;
  c2[0] = b&1;
  c2[1] = b&2;
  c2[2] = b&4;
  int ans = 0;
  if (c1[0]==0 && c2[0]==0)
  {
  }
  else
  {
    ans += 1;
  }
  if (c1[1]==0 && c2[1]==0)
  {
  }
  else
  {
    ans += 2;
  }
  if (c1[2]==0 && c2[2]==0)
  {
  }
  else
  {
    ans += 4;
  }
  
  printf("%d", ans);
  
  return 0;
}