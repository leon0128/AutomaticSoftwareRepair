#include <stdio.h>

/*
-----BEGIN EC PRIVATE KEY-----
MIHbAgEBBEE8eqikRbMDgYYOrXhOOkeGRuU/JUndy5kq7I1r3vRVFp+Q+fFMSDbl
ZbIH0YgMHKOWlvpOGVYQemgFiRdruDi656AHBgUrgQQAI6GBiQOBhgAEAOVl2gvS
vcvp+bu5OlUfHvKFoA8nRuvhHtcDFYda70GMBYuxfUfrvUuSe+nFTHCECRQYBChy
AOPjsWjmLeiloCbaAaAvNzMH0AlAvb/u3ySXkH5/+CiJJVx2vyap4o4VXIU7Cpgq
xjoyoqrBt2laQLnkayG5N14L0KNd8vxfMHi+qAwC
-----END EC PRIVATE KEY-----
*/

int main(void) {
  int Y;
  scanf("%d", &Y);
  puts(Y % 400 == 0 || (Y % 4 == 0 && Y % 100 != 0) ? "YES" : "NO");
  return 0;
}
