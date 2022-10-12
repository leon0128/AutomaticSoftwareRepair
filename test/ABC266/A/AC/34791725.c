#include <stdio.h>
#include <string.h>
 
void main (void)
{
  char S[99];
  int len = 0;
  int mid = 0;
  
  scanf("%s", S);
  len = strlen(S);
  mid = (len + 1) / 2;
  
  printf("%c", S[mid - 1]);
}