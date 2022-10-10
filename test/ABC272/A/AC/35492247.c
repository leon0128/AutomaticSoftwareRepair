#include <stdio.h> 
#include <stdlib.h> 
 
int main() { 
  int i=0, j=0; 
  int arr[10000]; 
  char temp; 
  int r =0;
  int s=0;
  int t =0;
  scanf("%d",&r);
  do { 
      scanf("%d%c", &arr[i], &temp); 
      i++; 
  } while(temp != &#39;\n&#39;); 
   
  while(s<=r) { 
      t +=arr[s];
      s++;
  } 
 
     printf("%d ",t); 

  return 0; 
}