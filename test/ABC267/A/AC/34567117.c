#include <stdio.h>
#include <string.h>

int main(){
 char s[100];
 scanf("%s", s, 100);
 char *youbi[5] = {
 	"Monday","Tuesday","Wednesday","Thursday","Friday"
 };
  for(int i=0;i<5;i++){
  	if(strcmp(s,youbi[i]) == 0){
      printf("%d",5-i);
    }
  }
}