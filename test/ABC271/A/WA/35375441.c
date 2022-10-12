#include <stdio.h>
int main(void) {
  
  int a[100][100], b[100][100];
  int k = 0,j = 0;
  
  for(k = 0; k<2; k++){
    scanf("%d",&a[j][k]);
  }
  
  
  for(j = 1; a[0][0] + 1 > j; j++){

    scanf("%d",&a[j][0]);
  
    for(k = 1; a[j][0]+1>k; k++){
      scanf("%d",&a[j][k]);
    }
  }
  
  for(j = 0; a[0][1] > j; j++){
    for(k = 0;  k < 2; k++){
      scanf("%d",&b[j][k]);
    }
  }
  
  
   for(int i = 0; i<a[0][1]; i++){
       printf("%d",a[b[i][0]][b[i][1]]);
       printf("\n");
   }
  return 0;
}