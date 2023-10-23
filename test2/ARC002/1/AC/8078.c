#include <stdlib.h>
#include <stdio.h>
 
int main(int argc, char *argv[])
{
  int Y;
  char buf[5];
  fgets(buf, 5, stdin);
  Y = strtol(buf, NULL, 10);
  if(Y % 4 == 0){
    if(Y % 100 == 0){
      if(Y % 400 == 0){
        printf("YES\n");
      }else{
        printf("NO\n");
      }
    }else{
      printf("YES\n");
    }
  }else{
    printf("NO\n");
  }
  return 0;
}