#include<stdio.h>

int main()
{
  int n;
  scanf("%d", &n);
  int shou, amari[2]={0};
  shou = n;
  for(int i=0; i < 2; ++i)
  {
    amari[i] = shou % 16;
    shou /= 16;
  }

  for(int i=1; i >= 0; --i)
  {
    if(amari[i] == 10)  printf("A");
    else if(amari[i] == 11)  printf("B");
    else if(amari[i] == 12)  printf("C");
    else if(amari[i] == 13)  printf("D");
    else if(amari[i] == 14)  printf("E");
    else if(amari[i] == 15)  printf("F");
    else  printf("%d", amari[i]);
  }
}
