#include<stdio.h>
 
int main(){
int n, m ,t;
int i,j;
char s[10];
  
scanf("%s",&s);
  
if(s[1]=='o'){
  printf("%d",5);
}else if(s[1]=='u'){
  printf("%d",4);
}else if(s[1]=='e'){
  printf("%d",3);
}else if(s[1]=='h'){
  printf("%d",2);
}else if(s[1]=='r'){
  printf("%d",1);
}
  
  return(0);
}