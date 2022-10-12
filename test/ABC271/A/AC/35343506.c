#include <stdio.h>
main(void){
  
  int i;
  int n;
  
  // input
  scanf("%d", &n);
  //printf("n:%d\n", n);
  
  // cal
  int a[2];
  char d[2];
  a[1] = n / 16;
  a[0] = n % 16;
  //printf("a:%d,%d\n", a[1],a[0]);
  
  for(i=0; i<2; i++){
  
    if(a[i] < 10){
      d[i] = (char) a[i] + '0';
    }else{
      d[i] = (char) (a[i]-10) + 'A';
    }
  }                 
  
  // output
  //printf("d:%c%c\n", d[1], d[0]);
  printf("%c%c\n", d[1], d[0]);
  
  return 0;
  
}