#include <stdio.h>
#include <string.h>
 
int main(void){
	char s[10];
	char days[5][10] = {"Monday","Tuesday","Wednesday","Thursday","Friday"};
	int i = 0;
 
	scanf("%s",s);
	
  	while(strcmp(s, days[i])==0){
		i++;
    }
	
	printf("%d",5-i);
  
  return 0;
}