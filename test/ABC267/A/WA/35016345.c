#include<stdio.h>
#include<string.h>
int main(){
  char s[10];
  char day[5][10]={"Monday","Tuesday","Wednesday","Thurthday","Friday"};
  int i;
  scanf("%s",s);
  
  for(i = 0;i<5;i++){
    if(strcmp(s,day[i])){
      printf("%d",5-i);
      break;
    }
  }
  
  return 0;
  
}