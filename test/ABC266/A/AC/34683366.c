#include<stdio.h>
#include <string.h>

const int mid (char* S){
  int a = strlen(S)/2 + 1;
  return S[a-1];
}
  
int main(){
  char str[100];
  scanf("%s",&str); 
  char midletter = mid(str);
  printf("%c", midletter);
  return 0;
}