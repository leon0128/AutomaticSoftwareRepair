#include<stdio.h>
int main()
{
  int N,Fst,Snd;
  scanf("%d",&N);
  Fst = N % 16;
  Snd = N / 16;
  if (Fst < 10)
    printf("%d", Fst);
  else if(Fst == 10)
    printf("A");
  else if(Fst == 11)
    printf("B");
  else if(Fst == 12)
    printf("C");
  else if(Fst == 13)
    printf("D");
  else if(Fst == 14)
    printf("E");
  else 
    printf("F");
  
  if (Snd < 10)
    printf("%d", Snd);
  else if(Snd == 10)
    printf("A");
  else if(Snd == 11)
    printf("B");
  else if(Snd == 12)
    printf("C");
  else if(Snd == 13)
    printf("D");
  else if(Snd == 14)
    printf("E");
  else 
    printf("F");
 
}