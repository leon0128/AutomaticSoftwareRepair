#include <stdio.h>
int main() {
int n;
  scanf("%d", &n);
  int a[n];
  for(int i=1; i<=n; i++){
  scanf("%d", &a[i]);
  }
  int k=a[0];
  for(int i=1; i<=n; i++){
  k = k+a[i]; 
  }
  printf("%d\n", k);

return 0;
}