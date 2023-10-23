#include <stdio.h>

int main(){
  char buf[256];
  int n;

  fgets(buf, 200, stdin);
  sscanf(buf, "%d", &n);

  if(n % 400 == 0){
    printf("YES\n");
    return 0;
  }

  if(n % 100 == 0){
    printf("NO\n");
    return 0;
  }

  if(n % 4 == 0){
    printf("YES\n");
    return 0;
  }

  printf("NO\n");

  return 0;
}