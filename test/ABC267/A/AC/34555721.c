#include <stdio.h>
#include<string.h>
int main(void)
{
  char S[15];
  scanf("%s",S);
  switch(S[2]){
    case 'n':
        printf("5");
      break;
     case 'e':
        printf("4");
      break; 
      case 'd':
        printf("3");
      break;
      case 'u':
        printf("2");
      break;
      case 'i':
        printf("1");
      break;
  }
  
  
  return 0;
}