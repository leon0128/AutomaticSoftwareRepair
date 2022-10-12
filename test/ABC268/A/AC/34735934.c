#include<stdio.h>
void main(){
  
  int integers[10];
  int a;
  int i, j;
  int count;
  
  count = 0;
  for( i = 0; i < 5; i++ ){
    scanf("%d", &a);
    for( j = 0; j < count; j++ ){
      if( integers[j] == a ) break;
    }
    if( j == count ) {
      integers[count] = a;
      count ++;
    }
  }
  
  printf("%d\n", count );
  return;
  
}
