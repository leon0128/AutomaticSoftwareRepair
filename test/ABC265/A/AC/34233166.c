#include<stdio.h>
main(){
  int x, y, n, one=0, two=0;
  scanf("%d%d%d", &x, &y, &n);
  one += x*n;
  int rem = n%3;
  two += (n/3)*y+ rem*x;
  printf("%d", (one<two)? one:two);
  
}
  