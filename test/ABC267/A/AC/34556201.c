#include <stdio.h>
#include <string.h>
 
int main(void){
  char buf[1000];
  char s[100];
  char *sm = "Monday";
  char *st = "Tuesday";
  char *sw = "Wednesday";
  char *sh = "Thursday";
  char *sf = "Friday";
  int a = 0;
  fgets(buf, sizeof(buf), stdin);
  sscanf(buf,"%s\n",s);
  
  if (strcmp(s,sm) == 0){
    a = 5;
  }else if(strcmp(s,st) == 0){
    a = 4;
  }else if(strcmp(s,sw) == 0){
    a = 3;
  }else if(strcmp(s,sh) == 0){
    a = 2;
  }else if(strcmp(s,sf) == 0){
    a = 1;
  }
  
  printf("%d\n",a);
  
  return 0;
}