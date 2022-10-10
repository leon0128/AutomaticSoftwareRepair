#include <stdio.h> 

 
int main() { 
  int a, i=0, t=0, sum=0; 

  scanf("%d", &a);
  int arr[a];
  do { 
      scanf("%d", &arr[i]); 
      i++; 
  } while(i < a); 
  do {
      sum += arr[t];
      t++;
  } while(t < a);
  
  printf("%d", sum);
   
   
 
  return 0; 
} 