#include<stdio.h>
int main()
{
  int n;
  scanf("%d",&n);
  if(n<16)
  {
      if(n==10) printf("0A");
            else if(n==11) printf("0B");
            else if(n==12) printf("0C");
            else if(n==13) printf("0D");
            else if(n==14) printf("0E");
            else if(n==15) printf("0F");
            else printf("0%d",n);
    n=0;
  }
  while(n>0)
  {
    if(n>=16)
      {
          int h;
          h=n%16;
          n=(n-n%16)/16;
          if(h==10) printf("A");
            else if(h==11) printf("B");
            else if(h==12) printf("C");
            else if(h==13) printf("D");
            else if(h==14) printf("E");
            else if(h==15) printf("F");
            else printf("%d",h);
      }
    else{
            int h;
            h=n%16;
            if(h==10) printf("A");
            else if(h==11) printf("B");
            else if(h==12) printf("C");
            else if(h==13) printf("D");
            else if(h==14) printf("E");
            else if(h==15) printf("F");
            else printf("%d",h);
        n=0;
    }
  }
  return 0;
}