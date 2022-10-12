#include<stdio.h>
#include<string.h>
int main(void){
  char a[10]="Monday",b[10]="Tuesday",c[10]="Wednesday",d[10]="Thursday",s[10];
  scanf("%s",s);
  if(strcmp(s,a)==0){
    printf("5");
  }
  else if(strcmp(s,b)==0){
    printf("4");
  }
  else if(strcmp(s,c)==0){
    printf("3");
  }
  else if(strcmp(s,d)==0){
    printf("2");
  }
  else{
    printf("1");
  }
  return 0;
}