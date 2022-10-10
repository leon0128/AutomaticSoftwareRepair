#include <stdio.h>
int main() {
int n;
  scanf("%d", &n);
  int a[n];
  for(int i=1; i<=n; i++){
  scanf("%d", &a[i]);
  }
  int k=0;
  for(int j=0; j<n; j++){
  k = k+a[j]; 
  }
  printf("%d\n", k);
 
return 0;
}