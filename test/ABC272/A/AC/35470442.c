#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
int main(){
   int a;
   scanf("%d", &a);
   int arr[a];
   int sum=0;
   for(int i=0;i<a;i++){
      scanf("%d", &arr[i]);
      sum=sum+arr[i];
   }
   printf("%d\n", sum);
  
   return 0;
}

