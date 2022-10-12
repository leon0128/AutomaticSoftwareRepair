#include <stdio.h>
#include <string.h>
int main() {

  char S[10];
  scanf("%s", S);

if (strcmp(S,"Monday")==0){
  printf("%d", 6-1);
}
else if (strcmp(S,"Tuesday")==0){
  printf("%d", 6-2);
}
  else if (strcmp(S,"Wednesday")==0){
  printf("%d", 6-3);
}
  else if (strcmp(S,"Thursday")==0){
  printf("%d", 6-4);
}
  else if (strcmp(S,"Friday")==0){
  printf("%d", 6-5);
}
  return 0;
}