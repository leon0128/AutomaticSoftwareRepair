#include<stdio.h>

int main(){
  char ans[20];
  char s1[10] = {"Monday"};
  char s2[10] = {"Tuesday"};
  char s3[10] = {"Wednesday"};
  char s4[10] = {"Thursday"};
  char s5[10] = {"Friday"};
  
  scanf("%s" , ans) ;
  if(strcmp(ans , s1 )==0) printf("5\n");
  if(strcmp(ans , s2 )==0) printf("4\n");
  if(strcmp(ans , s3 )==0) printf("3\n");
  if(strcmp(ans , s4 )==0) printf("2\n");
  if(strcmp(ans , s5 )==0) printf("1\n");

  return 0;
}