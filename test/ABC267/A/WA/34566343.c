#include <stdio.h>
#include <string.h>

int main(){
 char s[100];
 scanf("%s", s);
 char *youbi[5] = {
 	"Monday","Tuesday","Wednesday","Thursday","Friday"
 };
  for(int i=0;i<5;i++){
  	if(strcmp(s,youbi[i])){
      printf("%d",5-i);
    }
  }
}