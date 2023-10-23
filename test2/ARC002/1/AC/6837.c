#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define REP(i,a,b) for(i=a;i<b;i++)
#define rep(i,n) REP(i,0,n)

int isLeapYear(int y){if(y%400==0)return 1;if(y%100==0)return 0; if(y%4==0)return 1; return 0;}

int main(){
  int i,j,k,l,m,n;
  scanf("%d",&n);
  if(isLeapYear(n)) puts("YES"); else puts("NO");

  return 0;
}
