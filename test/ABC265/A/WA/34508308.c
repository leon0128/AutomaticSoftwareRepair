#include<stdio.h>
int main() {
  int x,y,n;
  int sum = 0;
  scanf("%d",&x);
  scanf("%d",&y);
  scanf("%d",&n);
  int ny = y/3;
  
  if (x <= ny) 
    printf("%d\n",x * n);
  else 
    sum = n/3 * y;
    int z = n % 3;
    sum += z * x;
    printf("%d",sum);
  return 0;
}