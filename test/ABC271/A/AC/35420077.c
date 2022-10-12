#include <stdio.h>

int main() {
  int n;
  scanf("%d", &n);
  int first = n/16;
  if(first == 10) {
    printf("A");
  }
  else if(first == 11) {
    printf("B");
  }
  else if(first == 12) {
    printf("C");
  }
  else if(first == 13) {
    printf("D");
  }
  else if(first == 14) {
    printf("E");
  }
  else if(first == 15) {
    printf("F");
  }
  else {
    printf("%d", first);
  }
  int second = n%16;
  if(second == 10) {
    printf("A");
  }
  else if(second == 11) {
    printf("B");
  }
  else if(second == 12) {
    printf("C");
  }
  else if(second == 13) {
    printf("D");
  }
  else if(second == 14) {
    printf("E");
  }
  else if(second == 15) {
    printf("F");
  }
  else {
    printf("%d", second);
  }
  printf("\n");
  return 0;
}