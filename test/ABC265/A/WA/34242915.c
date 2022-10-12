#include<stdio.h>

int main () {
  int n, m, t;
  int a[10000], x[10000], y[10000], z[10000];
  int to_m_count = 0;
  scanf("%d", &n);
  scanf("%d", &m);
  scanf("%d", &t);
  for(int j = 0; j <n-1; j++) {
    scanf("%d", &a[j]);
  }
  scanf("\n", &a[n-1]);
  for(int j = 0; j < m; j++) {
    scanf("%d", &x[j]);
    scanf("%d", &y[j]);
  }
  scanf("\n", &x[m-1]);
  scanf("\n", &y[m-1]);
  for (int j = 0; j < n-1; j++) {
    z[j] = 0;
  }
  for (int j = 0; j < n-1; j++) {
    if (x[to_m_count] > j) {
      to_m_count++;
    }
    else if(x[to_m_count] == j){
      z[j] = y[to_m_count];
    }
    else {}
  }
  for(int j = 0; j<n-1; j++) {
      t = t - a[j] + z[j];
      if (t <= 0) {
        break;
      }
  }
  if (t > 0) {
    printf("Yes");
  }
  else {
    printf("No");
  }
}