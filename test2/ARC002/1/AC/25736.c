#include <stdio.h>

int IsLeap(int);

int main(void){
  int year;
  char *s;
  
  scanf("%d", &year);
  
  if(IsLeap(year)){
    s = "YES";
  }else{
    s = "NO";
  }
  
  printf("%s\n", s);
  
  return 0;
}

int IsLeap(int year){
  if(year % 400 == 0){
    return 1;
  }else if(year % 100 == 0){
    return 0;
  }else if(year % 4 == 0){
    return 1;
  }else{
    return 0;
  }
}
