#include <stdio.h>
#define ToiA 1
#define ToiB 2
#define ToiC 4
int main() {
  int A = 0, B = 0;
  scanf("%d %d", &A, &B);
  int SUNUKE = 0;
  int FAa = 0, FAb = 0, FAc = 0;
  int FBa = 0, FBb = 0, FBc = 0;
  if (A - ToiC >= 0) {
    FAc = 1;
    SUNUKE += 4;
    A -= 4;
  }
  if (A - ToiB >= 0) {
    FAb = 1;
    SUNUKE += 2;
    A -= 2;
  }
  if (A - ToiA >= 0) {
    FAa = 1;
    SUNUKE += 1;
    A -= 1;
  }
  if (B - ToiC >= 0 && FAc != 1) {
    FBc = 1;
    SUNUKE += 4;
    B -= 4;
  }
  if (B - ToiB >= 0 && FAb != 1) {
    FBb = 1;
    SUNUKE += 2;
    B -= 2;
  }
  if (B - ToiA >= 0 && FAa != 1) {
    FBa = 1;
    SUNUKE += 1;
    B -= 1;
  }

  printf("%d\n", SUNUKE);
  return 0;
}