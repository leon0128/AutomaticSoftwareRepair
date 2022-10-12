#include<stdio.h>

void main(){
  
  int n;
  int p[100010];
  int max;
  
  int i, j;
  int count;
  
  scanf("%d\n", &n);
  for( i = 0; i < n; i++ ){
    scanf("%d", &p[i]);
  }
  
  max = 0;
  for( i = 0; i < n; i++ ){
  	count = 0;
  	for( j = 0; j < n; j++ ){
    	if( p[(j+i+1)%n] == j || p[(j+i)%n] == j){
            count++;
          }else if( j+i != 0 && p[(j+i-1)%n] == j ){
      	     count++;
           }else if( j+i == 0 && p[(j+i+n-1)%n] == j ){
             count++;
           }
 	 }
  	if( max < count ) max = count;
  }
    
  printf("%d\n", max);
  return;
  
}