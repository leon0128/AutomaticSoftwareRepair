#include<stdio.h>
#include<string.h>
int main()
  {
  size_t i=0;char c=getchar(),A[101];
  while(c>='a'&&c<='z'){A[i++]=c;c=getchar();}
  return !putchar(A[i>>1]);
  }