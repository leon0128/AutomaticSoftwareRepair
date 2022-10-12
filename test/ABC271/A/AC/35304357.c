#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int n, amari;
  scanf("%d", &n);
  amari = n % 16;
  n = (n - amari) / 16;
  if (n == 0) {
    printf("0");
  } else if (0 < n && n < 10) {
    printf("%d", n);
  } else if (n == 10) {
    printf("A");
  } else if (n == 11) {
    printf("B");
  } else if (n == 12) {
    printf("C");
  } else if (n == 13) {
    printf("D");
  } else if (n == 14) {
    printf("E");
  } else if (n == 15) {
    printf("F");
  }
  if (amari == 0) {
    printf("0");
  } else if (0 < amari && amari < 10) {
    printf("%d", amari);
  } else if (amari == 10) {
    printf("A");
  } else if (amari == 11) {
    printf("B");
  } else if (amari == 12) {
    printf("C");
  } else if (amari == 13) {
    printf("D");
  } else if (amari == 14) {
    printf("E");
  } else if (amari == 15) {
    printf("F");
  }
  return 0;
}