#include <stdio.h>
#include <string.h>
int main(void){
  
char s[100];
scanf("%s",&s);
  
int n=strlen(s);
  
printf("%c",s[(n+1)/2-1]);

return 0;
}