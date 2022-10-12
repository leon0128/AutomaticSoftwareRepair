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

int main (void)
{
  Uchar s[20];//文字列入力用
  scanf("%s", s);//文字列入力用
  if (0 == strcmp(s,"Monday"))
  {
    printf("5");
  }
  if (0 == strcmp(s,"Tuesday"))
  {
    printf("4");
  }
  if (0 == strcmp(s,"Wednesday"))
  {
    printf("3");
  }
  if (0 == strcmp(s,"Thursday"))
  {
    printf("2");
  }
  if (0 == strcmp(s,"Friday"))
  {
    printf("1");
  }
  return 0;
}