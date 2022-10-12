#include <stdio.h>  
#include <string.h>

int main()
{ 
  char *a="Monday";
  char *b="Tuesday";
  char *c="Wednesday";
  char *d="Thursday";
  char *e="Friday";

  char s[10];

  scanf("%s",&s);
  int a1 = strcmp(s, a);
  int b1 = strcmp(s, b);
  int c1 = strcmp(s, c);
  int d1 = strcmp(s, d);
  int e1 = strcmp(s, e);

  if(a1==0) printf("5");
  else if(b1==0) printf("4");
  else if(c1==0) printf("3");
  else if(d1==0) printf("2");
  else if(e1==0) printf("1");
} 