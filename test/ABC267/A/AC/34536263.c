#include<stdio.h>
#include<string.h>
int main(){
  char s[100];
  scanf("%s",s);
  
  if(strcmp(s,"Monday")==0){
    printf("5");
  }else if(strcmp(s,"Tuesday")==0){
    printf("4");
  }else if(strcmp(s,"Wednesday")==0){
    printf("3");
  }else if(strcmp(s,"Thursday")==0){
    printf("2");
  }else if(strcmp(s,"Friday")==0){
    printf("1");
  }
  
  return 0;
}