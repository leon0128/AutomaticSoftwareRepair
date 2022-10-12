#include<stdio.h>
#define MAX 100
int length(char str[]){
  int len=0;
  for(int i=0;str[i]!='\0';i++){
    len++;
  }
  return len;
}
int main(){
 char str[MAX];
 scanf("%s",str);
 int len=length(str);
 printf("%c\n",str[len/2]);
 return 0;
}