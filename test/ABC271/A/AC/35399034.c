#include<stdio.h>
int main()
{
  int n,k[2],i=0;
  scanf("%d",&n);
  if(n<10)
  {
      printf("0%d",n); return 0;
  }
  k[0]=n%16;
  if(n>=16)
  {
      n=n/16;
      k[1]=n%16;
  }
  else k[1]=0;

  if(k[1]==10) printf("A");
      else if(k[1]==11) printf("B");
      else if(k[1]==12) printf("C");
      else if(k[1]==13) printf("D");
      else if(k[1]==14) printf("E");
      else if(k[1]==15) printf("F");
      else printf("%d",k[1]);
if(k[0]==10) printf("A");
      else if(k[0]==11) printf("B");
      else if(k[0]==12) printf("C");
      else if(k[0]==13) printf("D");
      else if(k[0]==14) printf("E");
      else if(k[0]==15) printf("F");
      else printf("%d",k[0]);
  return 0;
}