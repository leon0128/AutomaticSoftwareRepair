#include <stdio.h>
#include <math.h>

int main() {
 
  char s[10];
  
   scanf("%s",s);
  
  if(s[1]=='o'){printf("5");return 0;}
  if(s[1]=='u'){printf("4");return 0;}
  if(s[1]=='e'){printf("3");return 0;}
  if(s[1]=='h'){printf("2");return 0;}
  if(s[1]=='r'){printf("1");return 0;}
  
 
  return 0;
}